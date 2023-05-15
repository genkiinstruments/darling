#include "AudioHardwareImplALSA.h"
#include <cassert>
#include <sched.h>

AudioHardwareImplALSA::AudioHardwareImplALSA(AudioObjectID myId)
        : AudioHardwareImpl(myId),
          interleaved_buffer(8192)
{
    m_name = CFSTR("ALSA");
    m_manufacturer = CFSTR("ALSA");
    m_uid = CFSTR("ALSA:SystemObject");

    const char* deviceID = "default"; // TODO

    const int err = snd_pcm_open(&pcm_handle, deviceID, SND_PCM_STREAM_PLAYBACK, SND_PCM_ASYNC);

    if (err < 0)
    {
        if (-err == EBUSY)
            printf("The device \"%s\" is busy (another application is using it)\n", deviceID);
        else if (-err == ENOENT)
            printf("The device \"%s\" is not available.", deviceID);
        else
            printf("Could not open output device \"%s\": %s (%d)", deviceID, snd_strerror(err), err);
    }
}

AudioHardwareImplALSA::~AudioHardwareImplALSA()
{
    if (pcm_handle != nullptr)
    {
        snd_pcm_close(pcm_handle);
    }
}

OSStatus AudioHardwareImplALSA::getPropertyData(const AudioObjectPropertyAddress* inAddress, UInt32 inQualifierDataSize,
                                                const void* inQualifierData, UInt32* ioDataSize, void* outData)
{
    printf("AudioHardwareImplALSA::getPropertyData %s\n", multichar_to_string(inAddress->mSelector).c_str());

    switch (inAddress->mSelector)
    {
        case kAudioHardwarePropertyDefaultInputDevice: // returns AudioDeviceID
            if (auto* devId = static_cast<AudioDeviceID*>(outData); devId && *ioDataSize >= sizeof(AudioDeviceID))
            {
                *devId = kAudioObjectSystemObject + 2;
            }
            *ioDataSize = sizeof(AudioDeviceID);
            return kAudioHardwareNoError;

        case kAudioHardwarePropertyDefaultOutputDevice: // returns AudioDeviceID
            if (auto* devId = static_cast<AudioDeviceID*>(outData); devId && *ioDataSize >= sizeof(AudioDeviceID))
            {
                *devId = kAudioObjectSystemObject + 1;
            }
            *ioDataSize = sizeof(AudioDeviceID);
            return kAudioHardwareNoError;

        case kAudioHardwarePropertyDefaultSystemOutputDevice:
            if (auto* devId = static_cast<AudioDeviceID*>(outData); devId && *ioDataSize >= sizeof(AudioDeviceID))
            {
                *devId = kAudioObjectSystemObject;
            }
            *ioDataSize = sizeof(AudioDeviceID);
            return kAudioHardwareNoError;

        case kAudioHardwarePropertyDevices:
        {
            if (auto* devId = static_cast<AudioDeviceID*>(outData); devId && *ioDataSize >= 2*sizeof(AudioDeviceID))
            {
                devId[0] = kAudioObjectSystemObject + 1; // output
                devId[1] = kAudioObjectSystemObject + 2; // input
            }
            *ioDataSize = sizeof(AudioDeviceID) * 2;
            return kAudioHardwareNoError;
        }

//        case kAudioDevicePropertyMute:
//        case kAudioDevicePropertyAvailableNominalSampleRates:
//        case kAudioDevicePropertyBufferFrameSizeRange:
        case kAudioDevicePropertyBufferFrameSize:
            if (auto* bs = static_cast<UInt32*>(outData); bs && *ioDataSize >= sizeof(UInt32))
                *bs = 512;

            *ioDataSize = sizeof(UInt32);
            return kAudioHardwareNoError;

//        case kAudioDevicePropertyDeviceIsAlive:
//        case kAudioDevicePropertyDataSources:
//        case kAudioDevicePropertyDataSourceNameForID:
//        case kAudioDevicePropertyDataSource:
//        case kAudioDevicePropertyNominalSampleRate:
//        case kAudioDevicePropertyStreamConfiguration:
//        case kAudioDevicePropertyLatency:
//        case kAudioDevicePropertySafetyOffset:
//        case kAudioDevicePropertyStreams:
//        case kAudioDevicePropertyDeviceNameCFString:
//            return kAudioHardwareNoError;
    }

//    assert(false);

    return AudioHardwareImpl::getPropertyData(inAddress, inQualifierDataSize, inQualifierData, ioDataSize, outData);
}

OSStatus AudioHardwareImplALSA::setPropertyData(const AudioObjectPropertyAddress* inAddress, UInt32 inQualifierDataSize,
                                                const void* inQualifierData, UInt32 inDataSize, const void* inData)
{
    printf("AudioHardwareImplALSA::setPropertyData %s\n", multichar_to_string(inAddress->mSelector).c_str());

    switch (inAddress->mSelector)
    {
        case kAudioDevicePropertyBufferFrameSize:
            // TODO
            return kAudioHardwareNoError;

        case kAudioDevicePropertyBufferSize:
        case kAudioDevicePropertyVolumeScalar:
        case kAudioDevicePropertyVolumeDecibels:
        case kAudioDevicePropertyStreamFormat:
        case kAudioHardwarePropertyDefaultOutputDevice:
        case kAudioHardwarePropertyDefaultInputDevice:
            return kAudioHardwareNoError;
    }

    return AudioHardwareImpl::setPropertyData(inAddress, inQualifierDataSize, inQualifierData, inDataSize, inData);
}

AudioHardwareStream* AudioHardwareImplALSA::createStream(AudioDeviceIOProc callback, void* clientData)
{
    assert(false);
}

OSStatus AudioHardwareImplALSA::isPropertySettable(const AudioObjectPropertyAddress* inAddress, Boolean* outIsSettable)
{
    switch (inAddress->mSelector)
    {
        case kAudioDevicePropertyVolumeScalar:
        case kAudioDevicePropertyVolumeDecibels:
        case kAudioDevicePropertyBufferFrameSize:
            *outIsSettable = true;
            return kAudioHardwareNoError;
    }

    *outIsSettable = false;
    return kAudioHardwareUnknownPropertyError;
}

OSStatus AudioHardwareImplALSA::start(AudioDeviceIOProcID inProcID, AudioTimeStamp* ioRequestedStartTime, UInt32 inFlags)
{
    assert(proc == nullptr);
    proc = inProcID;

    {
        snd_pcm_hw_params_t* hwParams;
        snd_pcm_hw_params_alloca (&hwParams);

        if (snd_pcm_hw_params_any(pcm_handle, hwParams) < 0)
        {
            // this is the error message that aplay returns when an error happens here,
            // it is a bit more explicit that "Invalid parameter"
            printf("Broken configuration for this PCM: no configurations available");
            return false;
        }

        if (snd_pcm_hw_params_set_access(pcm_handle, hwParams, SND_PCM_ACCESS_RW_INTERLEAVED) >= 0) // works better for plughw..
            is_interleaved = true;
        else if (snd_pcm_hw_params_set_access(pcm_handle, hwParams, SND_PCM_ACCESS_RW_NONINTERLEAVED) >= 0)
            is_interleaved = false;
        else
        {
            printf("Failed to set access\n");
            return false;
        }

        enum { isFloatBit = 1 << 16, isLittleEndianBit = 1 << 17, onlyUseLower24Bits = 1 << 18 };

        if (snd_pcm_hw_params_set_format(pcm_handle, hwParams, SND_PCM_FORMAT_FLOAT_LE) < 0)
        {
            printf("snd_pcm_hw_params_set_format failed");
            return false;
        }

        int bitDepth = SND_PCM_FORMAT_FLOAT_LE & 0xFF;

        int          dir              = 0;
        unsigned int periods          = 4;
        auto         samplesPerPeriod = (snd_pcm_uframes_t) frame_size;

        if (snd_pcm_hw_params_set_rate_near(pcm_handle, hwParams, &sample_rate, nullptr) < 0)
            return false;

        if (snd_pcm_hw_params_set_channels(pcm_handle, hwParams, num_channels) < 0)
            return false;

        if (snd_pcm_hw_params_set_periods_near(pcm_handle, hwParams, &periods, &dir) < 0)
            return false;

        if (snd_pcm_hw_params_set_period_size_near(pcm_handle, hwParams, &samplesPerPeriod, &dir) < 0)
            return false;

        if (snd_pcm_hw_params(pcm_handle, hwParams) < 0)
            return false;

        snd_pcm_uframes_t frames = 0;

        int latency = (int) frames * ((int) periods - 1); // (this is the method JACK uses to guess the latency..)

        if (snd_pcm_hw_params_get_period_size(hwParams, &frames, &dir) < 0 || snd_pcm_hw_params_get_periods(hwParams, &periods, &dir) < 0)
            latency = 0;

        printf("frames: %d, periods: %d, samplesPerPeriod: %d\n", (int) frames, (int) periods, (int) samplesPerPeriod);

        snd_pcm_sw_params_t* swParams;
        snd_pcm_sw_params_alloca (&swParams);
        snd_pcm_uframes_t boundary;

        if (snd_pcm_sw_params_current(pcm_handle, swParams) < 0 ||
            snd_pcm_sw_params_get_boundary(swParams, &boundary) < 0 ||
            snd_pcm_sw_params_set_silence_threshold(pcm_handle, swParams, 0) < 0 ||
            snd_pcm_sw_params_set_silence_size(pcm_handle, swParams, boundary) < 0 ||
            snd_pcm_sw_params_set_start_threshold(pcm_handle, swParams, samplesPerPeriod) < 0 ||
            snd_pcm_sw_params_set_stop_threshold(pcm_handle, swParams, boundary) < 0 ||
            snd_pcm_sw_params(pcm_handle, swParams) < 0)
        {
            return false;
        }

        printf("Num channels running: %u, is interleaved: %u\n", num_channels, is_interleaved);

    }

    // TODO: Check return codes (kXXX)
    pthread_attr_t attr{};
    pthread_attr_init(&attr);

    sched_param param{};
    pthread_attr_getschedparam(&attr, &param);
    param.sched_priority = sched_get_priority_max(SCHED_RR);
    pthread_attr_setschedparam(&attr, &param);

    pthread_create(&thread_handle, &attr, &thread_entry, static_cast<void*>(this));

    printf("start() fin\n");

    return kAudioHardwareNoError;
}

OSStatus AudioHardwareImplALSA::stop(AudioDeviceIOProcID inProcID)
{
    printf("stop()\n");
    proc = nullptr;

    thread_should_exit = true;

    return kAudioHardwareNoError;
}

OSStatus AudioHardwareImplALSA::getCurrentTime(AudioTimeStamp* outTime)
{
    assert(false);
}

OSStatus AudioHardwareImplALSA::translateTime(const AudioTimeStamp* inTime, AudioTimeStamp* outTime)
{
    assert(false);
}

OSStatus AudioHardwareImplALSA::getNearestStartTime(AudioTimeStamp* ioRequestedStartTime, UInt32 inFlags)
{
    assert(false);
}

OSStatus AudioHardwareImplALSA::setBufferSize(uint32_t bufferSize)
{
    assert(false);
}

void* AudioHardwareImplALSA::run()
{
    printf("run()\n");

    assert(pcm_handle != nullptr);
    assert(proc != nullptr);

    while (!thread_should_exit)
    {
        if (snd_pcm_wait(pcm_handle, 2000) < 0)
            break;

        auto avail = snd_pcm_avail_update(pcm_handle);

        if (avail < 0)
            if (snd_pcm_recover(pcm_handle, (int) avail, 0) < 0)
                break;

        AudioTimeStamp  inNow{};
        AudioBufferList inInputData{
                .mNumberBuffers = 0,
                .mBuffers = {},
        };
        AudioTimeStamp  inInputTime{};
        AudioBufferList outOutputData{
                .mNumberBuffers = 1,
                .mBuffers = {AudioBuffer{
                        .mNumberChannels = num_channels,
                        .mDataByteSize = static_cast<UInt32>(sizeof(float) * frame_size * num_channels),
                        .mData = static_cast<void*>(interleaved_buffer.data()),
                }},
        };
        AudioTimeStamp  inOutputTime{};

        assert(m_proc[proc].first != nullptr);
        m_proc[proc].first(m_myId, &inNow, &inInputData, &inInputTime, &outOutputData, &inOutputTime, m_proc[proc].second);

        const auto write_to_output_device = [&]
        {
            snd_pcm_sframes_t num_done = 0;

            if (is_interleaved)
            {
                num_done = snd_pcm_writei(pcm_handle, interleaved_buffer.data(), frame_size);
            }
            else
            {
                assert(false);
                // TODO: Deinterleave
//                num_done = snd_pcm_writen(handle, (void**) data, (snd_pcm_uframes_t) numSamples);
            }

            static int underrunCount = 0;

            if (num_done < 0)
            {
                if (num_done == -(EPIPE))
                    underrunCount++;

                if (auto e = snd_pcm_recover(pcm_handle, (int) num_done, 1 /* silent */); e < 0)
                {
                    printf("snd_pcm_recover fail: %d, num done: %lu, underrun count: %d\n", e, num_done, underrunCount);
                    return false;
                }
            }

            if (num_done < frame_size)
                printf("Did not write all samples: num_done: %lu, numSamples: %u\n", num_done, frame_size);

            return true;
        };

        if (!write_to_output_device())
        {
            printf("write failure\n");
            break;
        }
    }

    return nullptr;
}


