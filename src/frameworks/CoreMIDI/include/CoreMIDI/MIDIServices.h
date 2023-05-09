#ifndef __MIDIServices_h__
#define __MIDIServices_h__

#include <CoreFoundation/CoreFoundation.h>

#ifdef __cplusplus
#define COREMIDI_EXPORT extern "C"
#else
#define COREMIDI_EXPORT
#endif

extern const CFStringRef kMIDIPropertyName;
extern const CFStringRef kMIDIPropertyConnectionUniqueID;
extern const CFStringRef kMIDIPropertyUniqueID;

typedef CF_ENUM(SInt32, MIDINotificationMessageID)
{
    kMIDIMsgSetupChanged           = 1,
    kMIDIMsgObjectAdded            = 2,
    kMIDIMsgObjectRemoved          = 3,
    kMIDIMsgPropertyChanged        = 4,
    kMIDIMsgThruConnectionsChanged = 5,
    kMIDIMsgSerialPortOwnerChanged = 6,
    kMIDIMsgIOError                = 7
};

CF_ENUM(OSStatus)
{
    kMIDIInvalidClient     = -10830,
    kMIDIInvalidPort       = -10831,
    kMIDIWrongEndpointType = -10832,
    kMIDINoConnection      = -10833,
    kMIDIUnknownEndpoint   = -10834,
    kMIDIUnknownProperty   = -10835,
    kMIDIWrongPropertyType = -10836,
    kMIDINoCurrentSetup    = -10837,
    kMIDIMessageSendErr    = -10838,
    kMIDIServerStartErr    = -10839,
    kMIDISetupFormatErr    = -10840,
    kMIDIWrongThread       = -10841,
    kMIDIObjectNotFound    = -10842,
    kMIDIIDNotUnique       = -10843,
    kMIDINotPermitted      = -10844,
    kMIDIUnknownError      = -10845
};

typedef struct MIDINotification
{
    MIDINotificationMessageID messageID;
    UInt32                    messageSize;
}                        MIDINotification;

typedef void (* MIDINotifyProc)(const MIDINotification* message, void* refCon);
typedef void (^MIDINotifyBlock)(const MIDINotification* message);

typedef UInt32        MIDIObjectRef;
typedef MIDIObjectRef MIDIClientRef;
typedef MIDIObjectRef MIDIEndpointRef;
typedef MIDIObjectRef MIDIEntityRef;
typedef MIDIObjectRef MIDIDeviceRef;
typedef MIDIObjectRef MIDIPortRef;

typedef UInt64 MIDITimeStamp;

#pragma pack(push, 4)

typedef struct MIDIPacket
{
    MIDITimeStamp timeStamp;
    UInt16        length;
    Byte          data[256];
}              MIDIPacket;

typedef struct MIDIPacketList
{
    UInt32     numPackets;
    MIDIPacket packet[1];
}              MIDIPacketList;

#pragma pack(pop)

typedef void (* MIDIReadProc)(const MIDIPacketList* pktlist, void* readProcRefCon, void* srcConnRefCon);

COREMIDI_EXPORT OSStatus MIDIClientCreate(CFStringRef name, MIDINotifyProc notifyProc, void* notifyRefCon, MIDIClientRef* outClient);
COREMIDI_EXPORT OSStatus MIDIClientCreateWithBlock(CFStringRef name, MIDIClientRef* outClient, MIDINotifyBlock notifyBlock);
COREMIDI_EXPORT OSStatus MIDIClientDispose(MIDIClientRef client);

COREMIDI_EXPORT ItemCount MIDIGetNumberOfSources(void);
COREMIDI_EXPORT ItemCount MIDIGetNumberOfDestinations(void);

COREMIDI_EXPORT MIDIEndpointRef MIDIGetSource(ItemCount sourceIndex0);
COREMIDI_EXPORT MIDIEndpointRef MIDIGetDestination(ItemCount destIndex0);

COREMIDI_EXPORT OSStatus MIDIObjectGetDataProperty(MIDIObjectRef obj, CFStringRef propertyID, CFDataRef _Nullable* outData);
COREMIDI_EXPORT OSStatus MIDIEndpointGetEntity(MIDIEndpointRef inEndpoint, MIDIEntityRef* outEntity);
COREMIDI_EXPORT OSStatus MIDIObjectGetStringProperty(MIDIObjectRef obj, CFStringRef propertyID, CFStringRef _Nullable* str);
COREMIDI_EXPORT OSStatus MIDIObjectGetIntegerProperty(MIDIObjectRef obj, CFStringRef propertyID, SInt32* outValue);

COREMIDI_EXPORT OSStatus MIDIEntityGetDevice(MIDIEntityRef inEntity, MIDIDeviceRef* outDevice);
COREMIDI_EXPORT OSStatus MIDIInputPortCreate(MIDIClientRef client, CFStringRef portName, MIDIReadProc readProc, void* refCon, MIDIPortRef* outPort);
COREMIDI_EXPORT OSStatus MIDIPortConnectSource(MIDIPortRef port, MIDIEndpointRef source, void *connRefCon);

#endif // __MIDIServices_h__
