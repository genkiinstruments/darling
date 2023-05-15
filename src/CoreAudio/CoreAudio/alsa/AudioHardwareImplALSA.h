#ifndef AUDIOHARDWAREIMPLALSA_H
#define AUDIOHARDWAREIMPLALSA_H

#include "../AudioHardwareImpl.h"
#include <alsa/asoundlib.h>
#include <pthread.h>
#include <vector>

class AudioHardwareImplALSA : public AudioHardwareImpl
{
public:
    explicit AudioHardwareImplALSA(AudioObjectID myId);
    ~AudioHardwareImplALSA() override;

    OSStatus isPropertySettable(const AudioObjectPropertyAddress* inAddress, Boolean* outIsSettable) override;

    OSStatus getPropertyData(const AudioObjectPropertyAddress* inAddress, UInt32 inQualifierDataSize,
                             const void* inQualifierData, UInt32* ioDataSize, void* outData) override;

    OSStatus setPropertyData(const AudioObjectPropertyAddress* inAddress, UInt32 inQualifierDataSize,
                             const void* inQualifierData, UInt32 inDataSize, const void* inData) override;

    OSStatus start(AudioDeviceIOProcID inProcID, AudioTimeStamp* ioRequestedStartTime, UInt32 inFlags) override;

    OSStatus stop(AudioDeviceIOProcID inProcID) override;

    OSStatus getCurrentTime(AudioTimeStamp* outTime) override;

    OSStatus translateTime(const AudioTimeStamp* inTime,
                           AudioTimeStamp* outTime) override;

    OSStatus getNearestStartTime(AudioTimeStamp* ioRequestedStartTime,
                                 UInt32 inFlags) override;
    OSStatus setBufferSize(uint32_t bufferSize) override;
protected:
    AudioHardwareStream* createStream(AudioDeviceIOProc callback, void* clientData) override;

private:
    static void* thread_entry(void* arg) { return static_cast<AudioHardwareImplALSA*>(arg)->run(); }
    void* run();

    std::vector<float> interleaved_buffer;
    bool               is_interleaved = true;
    unsigned int       num_channels   = 2;
    unsigned int       frame_size     = 512;
    unsigned int       sample_rate    = 44100;

    AudioDeviceIOProc proc = nullptr;

    snd_pcm_t* pcm_handle = nullptr;

    std::atomic_bool thread_should_exit = false;
    pthread_t        thread_handle      = nullptr;
};

#endif // AUDIOHARDWAREIMPLALSA_H