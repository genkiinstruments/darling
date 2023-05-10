#ifndef DARLING_ALSAMIDI_H
#define DARLING_ALSAMIDI_H

#include <memory>
#include <string>
#include <vector>
#include <alsa/asoundlib.h>
#include <map>
#include "CoreMIDI/MIDIServices.h"

// Forward declarations to allow struct instances to reference their owner
struct MidiDevice;
struct MidiClient;
struct MidiEntity;
struct MidiPort;

/*
 * MIDI Objects have properties, and often have an owning object, from which they inherit any properties they don’t define themselves.
 * Developers may add their own private properties, with names that begin with their company’s inverted domain name,
 * but with underscores instead of dots. For example, com_apple_APrivateAppleProperty.
 */
struct MidiObject
{
    MidiObject() : ref(getNextRefId()) { objects.insert({getRef(), this}); }

    virtual ~MidiObject() { objects.erase(getRef()); }

    MidiObject(const MidiObject&) = delete;
    MidiObject(MidiObject&&) = delete;
    MidiObject& operator=(const MidiObject&) = delete;
    MidiObject& operator=(MidiObject&&) = delete;

    template<typename T = MidiObject>
    static T* get(MIDIObjectRef ref) { return dynamic_cast<T*>(objects.at(ref)); }

    virtual OSStatus getDataProperty(CFStringRef propertyID, CFDataRef _Nullable* outData)
    {
        printf("MidiObject::getDataProperty, %s\n", CFStringGetCStringPtr(propertyID, kCFStringEncodingUTF8));
        return kMIDIUnknownProperty;
    }

    virtual OSStatus getStringProperty(CFStringRef propertyID, CFStringRef _Nullable* str)
    {
        printf("MidiObject::getStringProperty, %s\n", CFStringGetCStringPtr(propertyID, kCFStringEncodingUTF8));
        return kMIDIUnknownProperty;
    }

    virtual OSStatus getIntegerProperty(CFStringRef propertyID, SInt32* outValue)
    {
        printf("MidiObject::getIntegerProperty, %s\n", CFStringGetCStringPtr(propertyID, kCFStringEncodingUTF8));
        return kMIDIUnknownProperty;
    }

    [[nodiscard]] MIDIObjectRef getRef() const { return ref; }

private:
    static MIDIObjectRef getNextRefId()
    {
        static MIDIObjectRef id = 0;

        return ++id;
    }

    static inline std::map<MIDIObjectRef, MidiObject*> objects{};

    const MIDIObjectRef ref = 0;
};

/*
 * An endpoint object derives from MIDIObjectRef. It’s owned by a MIDIEntityRef, unless it’s a virtual endpoint,
 * in which case it has no owner. An entity may have any number of MIDI endpoints,
 * which contain sources and destinations of 16-channel MIDI streams.
 */
struct MidiEndpoint : public MidiObject
{
    MidiEndpoint(const MidiEntity& owner, std::string_view name, int portId, bool isInput);

    OSStatus getEntity(MIDIEntityRef* outEntity) const;

    OSStatus getStringProperty(CFStringRef propertyID, CFStringRef _Nullable* str) override;

    const MidiEntity& entity;
    const std::string name;
    const int         portId;
    bool              isInput;
};

/*
 * An entity object derives from MIDIObjectRef, and its owning object is a MIDIDeviceRef.
 * Devices may have multiple logically distinct subcomponents; for example, a MIDI synthesizer and a pair of MIDI ports are addressable using a USB port.
 * By grouping a device’s endpoints into entities, the system has enough information for an app to make reasonable assumptions about how to communicate
 * bidirectionally with each entity, as required by MIDI librarian apps.
 */
struct MidiEntity : public MidiObject
{
    MidiEntity(const MidiDevice& dev, std::string_view nm, int sourceClientId);

    OSStatus getDevice(MIDIDeviceRef* outDevice) const;

    OSStatus getStringProperty(CFStringRef propertyID, CFStringRef _Nullable* str) override;

    const MidiDevice& device;
    const std::string                          name;
    const int                                  clientId;
    std::vector<std::unique_ptr<MidiEndpoint>> endpoints;
};

/* A device object derives from MIDIObjectRef. It doesn’t have an owning object. */
struct MidiDevice : public MidiObject
{
    MidiDevice(snd_seq_t* handle, snd_seq_client_info_t* clientInfo);

    std::vector<std::unique_ptr<MidiEntity>> entities;
};

struct MidiPort : public MidiObject
{
    MidiPort(MidiClient& cl, bool isInput, std::string_view name, MIDIReadProc readProc, void* refCon);

    ~MidiPort() override;

    MidiClient& client;
    int          portId   = -1;
    MIDIReadProc readProc = nullptr;
    void* refCon = nullptr;
};

/* A client object derives from MIDIObjectRef. It doesn’t have an owning object. */
struct MidiClient : MidiObject
{
    MidiClient(const char*, MIDINotifyProc, void* notifyRefCon);

    ~MidiClient() override;

    OSStatus createPort(bool isInput, std::string_view name, MIDIReadProc readProc, void* refCon, MIDIPortRef* outPort);

    OSStatus disposePort(MidiPort& port);

    OSStatus connect(MidiPort& port, MidiEndpoint& source, void* connRefCon);

    OSStatus disconnect(MidiPort& port, MidiEndpoint& source);

    static void* thread_entry(void* arg) { return static_cast<MidiClient*>(arg)->run(); }
    void* run();

    struct Connection
    {
        MidiPort    * port;
        MidiEndpoint* source;
        void        * refCon;
    };

    std::vector<Connection> connections;
    std::atomic_bool        thread_should_exit = false;
    pthread_t               thread_handle      = nullptr;

    snd_seq_t* handle = nullptr;
    MIDINotifyProc proc = nullptr;
    void* notifyRefCon = nullptr;
    int clientId = -1;

    std::vector<std::unique_ptr<MidiPort>> ports;
};

//======================================================================================================================
struct AlsaMidi
{
    static OSStatus createClient(CFStringRef name, MIDINotifyProc notifyProc, void* notifyRefCon, MIDIClientRef* outClient);
    static OSStatus disposeClient(MIDIClientRef client);

    static ItemCount getNumberOfDestinations();
    static ItemCount getNumberOfSources();
    static MIDIEndpointRef getSource(ItemCount idx);
    static MIDIEndpointRef getDestination(ItemCount idx);

private:
    static inline std::unique_ptr<AlsaMidi> instance = nullptr;
    static AlsaMidi& getInstance()
    {
        if (instance == nullptr)
            instance = std::make_unique<AlsaMidi>();

        return *instance;
    }

    static std::pair<ItemCount, MIDIEndpointRef> getNumIO(bool wantsInput, std::optional<ItemCount> ioToSelect = std::nullopt);

    void enumerate();

    std::map<std::string, std::unique_ptr<MidiDevice>> devices;
    std::vector<std::unique_ptr<MidiClient>>           clients;
};

#endif //DARLING_ALSAMIDI_H
