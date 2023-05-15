#include "AudioHardwareImplALSAOutput.h"

AudioHardwareImplALSAOutput::AudioHardwareImplALSAOutput(AudioObjectID myId) : AudioHardwareImplALSA(myId)
{

}

OSStatus
AudioHardwareImplALSAOutput::getPropertyData(const AudioObjectPropertyAddress* inAddress, UInt32 inQualifierDataSize,
                                             const void* inQualifierData, UInt32* ioDataSize, void* outData)
{
    if (inAddress->mSelector == kAudioDevicePropertyStreamConfiguration)
    {
        size_t size = sizeof(AudioBufferList);

        if (inAddress->mScope == kAudioDevicePropertyScopeOutput)
            size += 1* sizeof(AudioBuffer);

        // Number of returned buffers is the number of channels
        if (AudioBufferList* abl = static_cast<AudioBufferList*>(outData); abl && *ioDataSize >= size)
        {
            if (inAddress->mScope == kAudioDevicePropertyScopeOutput)
            {
                abl->mNumberBuffers = 1;
                abl->mBuffers[0].mNumberChannels = 2;

                // TODO: Is the below stuff ever used? How?
                abl->mBuffers[0].mData = nullptr;
                abl->mBuffers[0].mDataByteSize = 0;
            }
            else
                abl->mNumberBuffers = 0;
        }

        *ioDataSize = size;
        return kAudioHardwareNoError;
    }

    return AudioHardwareImplALSA::getPropertyData(inAddress, inQualifierDataSize, inQualifierData, ioDataSize, outData);
}

OSStatus
AudioHardwareImplALSAOutput::setPropertyData(const AudioObjectPropertyAddress* inAddress, UInt32 inQualifierDataSize,
                                             const void* inQualifierData, UInt32 inDataSize, const void* inData)
{
    return AudioHardwareImplALSA::setPropertyData(inAddress, inQualifierDataSize, inQualifierData, inDataSize, inData);
}

AudioHardwareStream* AudioHardwareImplALSAOutput::createStream(AudioDeviceIOProc callback, void* clientData)
{
    return AudioHardwareImplALSA::createStream(callback, clientData);
}
