#import <CoreMIDI/MIDIServices.h>

#include "AlsaMidi.h"

const CFStringRef kMIDIPropertyName               = CFSTR("name");
const CFStringRef kMIDIPropertyConnectionUniqueID = CFSTR("connUniqueID");
const CFStringRef kMIDIPropertyUniqueID           = CFSTR("uniqueID");

#define STUB() printf("STUB called: %s\n", __PRETTY_FUNCTION__)

OSStatus MIDIClientCreate(CFStringRef name, MIDINotifyProc notifyProc, void* notifyRefCon, MIDIClientRef* outClient)
{
    return AlsaMidi::createClient(name, notifyProc, notifyRefCon, outClient);
}

// https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ProgrammingWithObjectiveC/WorkingwithBlocks/WorkingwithBlocks.html
OSStatus MIDIClientCreateWithBlock(CFStringRef name, MIDIClientRef* outClient, MIDINotifyBlock notifyBlock)
{
    STUB();
    return noErr;
}

OSStatus MIDIClientDispose(MIDIClientRef client)
{
    return AlsaMidi::disposeClient(client);
}

ItemCount MIDIGetNumberOfSources(void)
{
    return AlsaMidi::getNumberOfSources();
}

ItemCount MIDIGetNumberOfDestinations(void)
{
    return AlsaMidi::getNumberOfDestinations();
}

MIDIEndpointRef MIDIGetSource(ItemCount sourceIndex0)
{
    return AlsaMidi::getSource(sourceIndex0);
}

MIDIEndpointRef MIDIGetDestination(ItemCount destIndex0)
{
    return AlsaMidi::getDestination(destIndex0);
}

OSStatus MIDIEndpointGetEntity(MIDIEndpointRef inEndpoint, MIDIEntityRef* outEntity)
{
    if (auto* endp = dynamic_cast<MidiEndpoint*>(MidiObject::get(inEndpoint)); endp != nullptr)
        return endp->getEntity(outEntity);

    return kMIDIObjectNotFound;
}

OSStatus MIDIObjectGetDataProperty(MIDIObjectRef ref, CFStringRef propertyID, CFDataRef _Nullable* outData)
{
    if (auto* obj = MidiObject::get(ref); obj != nullptr)
        return obj->getDataProperty(propertyID, outData);

    return kMIDIObjectNotFound;
}

OSStatus MIDIObjectGetStringProperty(MIDIObjectRef ref, CFStringRef propertyID, CFStringRef _Nullable* str)
{
    if (auto* obj = MidiObject::get(ref); obj != nullptr)
        return obj->getStringProperty(propertyID, str);

    return kMIDIObjectNotFound;
}

OSStatus MIDIObjectGetIntegerProperty(MIDIObjectRef ref, CFStringRef propertyID, SInt32* outValue)
{
    if (auto* obj = MidiObject::get(ref); obj != nullptr)
        return obj->getIntegerProperty(propertyID, outValue);

    return kMIDIObjectNotFound;
}

OSStatus MIDIEntityGetDevice(MIDIEntityRef inEntity, MIDIDeviceRef* outDevice)
{
    if (auto* ent = dynamic_cast<MidiEntity*>(MidiObject::get(inEntity)); ent != nullptr)
        return ent->getDevice(outDevice);

    return kMIDIObjectNotFound;
}


OSStatus MIDIInputPortCreate(MIDIClientRef clientRef, CFStringRef portName, MIDIReadProc readProc, void* refCon, MIDIPortRef* outPort)
{
    if (auto* client = MidiObject::get<MidiClient>(clientRef); client != nullptr)
    {
        return client->createPort(true, CFStringGetCStringPtr(portName, kCFStringEncodingUTF8), readProc, refCon, outPort);
    }

    return kMIDIObjectNotFound;
}

OSStatus MIDIPortConnectSource(MIDIPortRef portRef, MIDIEndpointRef sourceRef, void* connRefCon)
{
    if (auto* port = MidiObject::get<MidiPort>(portRef); port != nullptr)
    {
        if (auto* endp = MidiObject::get<MidiEndpoint>(sourceRef); endp != nullptr)
        {
            return port->client.connect(*port, *endp, connRefCon);
        }
    }

    return kMIDIObjectNotFound;
}

OSStatus MIDIPortDisconnectSource(MIDIPortRef portRef, MIDIEndpointRef sourceRef)
{
    if (auto* port = MidiObject::get<MidiPort>(portRef); port != nullptr)
    {
        if (auto* endp = MidiObject::get<MidiEndpoint>(sourceRef); endp != nullptr)
        {
            return port->client.disconnect(*port, *endp);
        }
    }

    return kMIDIObjectNotFound;
}

OSStatus MIDIPortDispose(MIDIPortRef portRef)
{
    if (auto* port = MidiObject::get<MidiPort>(portRef); port != nullptr)
    {
        return port->client.disposePort(*port);
    }

    return kMIDIObjectNotFound;
}
