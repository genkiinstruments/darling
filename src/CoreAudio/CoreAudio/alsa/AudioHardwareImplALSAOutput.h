#ifndef AUDIOHARDWAREIMPLALSAOUTPUT_H
#define AUDIOHARDWAREIMPLALSAOUTPUT_H

#include "AudioHardwareImplALSA.h"

class AudioHardwareImplALSAOutput : public AudioHardwareImplALSA
{
public:
    AudioHardwareImplALSAOutput(AudioObjectID myId);

    OSStatus getPropertyData(const AudioObjectPropertyAddress* inAddress, UInt32 inQualifierDataSize,
                             const void* inQualifierData, UInt32* ioDataSize, void* outData) override;

    OSStatus setPropertyData(const AudioObjectPropertyAddress* inAddress, UInt32 inQualifierDataSize,
                             const void* inQualifierData, UInt32 inDataSize, const void* inData) override;
protected:
    AudioHardwareStream* createStream(AudioDeviceIOProc callback, void* clientData) override;
};

#endif // AUDIOHARDWAREIMPLALSAOUTPUT_H
