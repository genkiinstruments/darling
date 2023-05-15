#include "AlsaMidi.h"
#include <pthread.h>

#define EXPECT_OK(ret) assert((ret) >= 0 && snd_strerror(ret))

//======================================================================================================================
MidiClient::MidiClient(const char* nm, MIDINotifyProc pr, void* refCon)
        : proc(pr),
          notifyRefCon(refCon)
{
    EXPECT_OK(snd_seq_open(&handle, "default", SND_SEQ_OPEN_DUPLEX, 0));
    EXPECT_OK(snd_seq_nonblock(handle, SND_SEQ_NONBLOCK));
    EXPECT_OK(snd_seq_set_client_name(handle, nm));

    snd_seq_client_info_t* clientInfo = nullptr;
    snd_seq_client_info_alloca (&clientInfo);
    EXPECT_OK(snd_seq_get_client_info(handle, clientInfo));

    clientId = snd_seq_client_info_get_client(clientInfo);
}

MidiClient::~MidiClient()
{
    if (handle != nullptr)
        EXPECT_OK(snd_seq_close(handle));
}

OSStatus MidiClient::createPort(bool isInput, std::string_view name, MIDIReadProc readProc, void* refCon, MIDIPortRef* outPort)
{
    auto& p = ports.emplace_back(std::make_unique<MidiPort>(*this, isInput, name, readProc, refCon));

    *outPort = p->getRef();

    return noErr;
}

OSStatus MidiClient::disposePort(MidiPort& port)
{
    ports.erase(std::find_if(ports.begin(), ports.end(), [&](const auto& p) { return p.get() == &port; }));

    return noErr;
}

OSStatus MidiClient::connect(MidiPort& port, MidiEndpoint& source, void* connRefCon)
{
    EXPECT_OK(snd_seq_connect_from(handle, port.portId, source.entity.clientId, source.portId));
    connections.push_back(Connection{&port, &source, connRefCon});

    if (connections.size() == 1)
        pthread_create(&thread_handle, nullptr, &thread_entry, this);

    return noErr;
}

OSStatus MidiClient::disconnect(MidiPort& port, MidiEndpoint& source)
{
    const auto it = std::find_if(connections.begin(), connections.end(), [&](const auto& c) { return c.port == &port; });

    if (it != connections.end())
    {
        EXPECT_OK(snd_seq_disconnect_from(handle, port.portId, it->source->entity.clientId, it->source->portId));
        connections.erase(it);
    }

    if (connections.empty())
    {
        thread_should_exit = true;
        pthread_join(thread_handle, nullptr);
    }

    return noErr;
}

void* MidiClient::run()
{
    printf("MidiClient::run()\n");

    const int maxEventSize = 16 * 1024;
    snd_midi_event_t* midiParser = nullptr;

    if (snd_midi_event_new(maxEventSize, &midiParser) >= 0)
    {
        auto numPfds = snd_seq_poll_descriptors_count(handle, POLLIN);

        std::vector<pollfd> pfd(numPfds);
        EXPECT_OK(snd_seq_poll_descriptors(handle, pfd.data(), (unsigned int) numPfds, POLLIN));

        std::vector<uint8_t> buffer(maxEventSize);

        while (!thread_should_exit)
        {
            if (poll(pfd.data(), (nfds_t) numPfds, 100) > 0)
            {
                if (thread_should_exit)
                    break;

                do
                {
                    snd_seq_event_t* inputEvent = nullptr;

                    if (snd_seq_event_input(handle, &inputEvent) >= 0)
                    {
                        const auto numBytes = snd_midi_event_decode(midiParser, buffer.data(), maxEventSize, inputEvent);

                        if (numBytes <= 0)
                            continue;

                        snd_midi_event_reset_decode(midiParser);

                        MIDIPacket packet{
                                .timeStamp = MIDITimeStamp(inputEvent->time.time.tv_sec),
                                .length = static_cast<UInt16>(numBytes),
                                .data = {},
                        };

                        const auto it = std::find_if(connections.begin(), connections.end(), [&](const Connection& c)
                        {
                            // TODO: port->client.clientId is just this->clientId?

                            return c.source->entity.clientId == inputEvent->source.client &&
                                   c.source->portId == inputEvent->source.port &&
                                   c.port->portId == inputEvent->dest.port &&
                                   c.port->client.clientId == inputEvent->dest.client;
                        });

                        if (it != connections.end())
                        {
                            std::memcpy(packet.data, buffer.data(), numBytes);

                            const MIDIPacketList packetList{
                                    .numPackets = 1,
                                    .packet = {packet},
                            };

                            auto& port       = *it->port;
                            auto* connRefCon = it->refCon;

                            port.readProc(&packetList, port.refCon, connRefCon);
                        }

                        EXPECT_OK(snd_seq_free_event(inputEvent));
                    }
                } while (snd_seq_event_input_pending(handle, 0) > 0);
            }
        }

        snd_midi_event_free(midiParser);
    }

    printf("MidiClient thread done\n");

    return nullptr;
}

//======================================================================================================================
MidiEndpoint::MidiEndpoint(const MidiEntity& owner, std::string_view nm, int port, bool isInput)
        : entity(owner),
          name(nm),
          portId(port),
          isInput(isInput)
{

}

OSStatus MidiEndpoint::getEntity(MIDIEntityRef* outEntity) const
{
    *outEntity = entity.getRef();
    return noErr;
}

OSStatus MidiEndpoint::getStringProperty(CFStringRef propertyID, CFStringRef* str)
{
    if (CFStringCompare(kMIDIPropertyName, propertyID, 0) == kCFCompareEqualTo)
    {
        *str = CFStringCreateWithCString(kCFAllocatorDefault, name.c_str(), kCFStringEncodingUTF8);
        return noErr;
    }
    else if (CFStringCompare(kMIDIPropertyUniqueID, propertyID, 0) == kCFCompareEqualTo)
    {
        // TODO: Is this enough?
        *str = CFStringCreateWithCString(kCFAllocatorDefault, (name + (isInput ? " IN" : " OUT")).c_str(), kCFStringEncodingUTF8);
        return noErr;
    }

    return MidiObject::getStringProperty(propertyID, str);
}

//======================================================================================================================
MidiEntity::MidiEntity(const MidiDevice& dev, std::string_view nm, int sourceClientId)
        : device(dev),
          name(nm),
          clientId(sourceClientId)
{

}

OSStatus MidiEntity::getStringProperty(CFStringRef propertyID, CFStringRef* str)
{
    if (CFStringCompare(kMIDIPropertyName, propertyID, 0) == kCFCompareEqualTo)
    {
        *str = CFStringCreateWithCString(kCFAllocatorDefault, name.c_str(), kCFStringEncodingUTF8);
        return noErr;
    }

    return MidiObject::getStringProperty(propertyID, str);
}

OSStatus MidiEntity::getDevice(MIDIDeviceRef* outDevice) const
{
    *outDevice = device.getRef();
    return noErr;
}

//======================================================================================================================
MidiDevice::MidiDevice(snd_seq_t* handle, snd_seq_client_info_t* clientInfo)
{
    snd_seq_port_info_t* portInfo = nullptr;

    snd_seq_port_info_alloca (&portInfo);
    assert (portInfo != nullptr);
    const auto             numPorts     = snd_seq_client_info_get_num_ports(clientInfo);
    const auto             sourceClient = snd_seq_client_info_get_client(clientInfo);
    const std::string_view clientName   = snd_seq_client_info_get_name(clientInfo);

    snd_seq_port_info_set_client(portInfo, sourceClient);
    snd_seq_port_info_set_port(portInfo, -1);

    auto entity = std::make_unique<MidiEntity>(*this, clientName, sourceClient);

    for (int p = 0; p < numPorts; ++p)
    {
        if (snd_seq_query_next_port(handle, portInfo) == 0)
        {
            const auto             caps     = snd_seq_port_info_get_capability(portInfo);
            const auto             portID   = snd_seq_port_info_get_port(portInfo);
            const std::string_view portName = snd_seq_port_info_get_name(portInfo);

            printf("  Port name: %s, id: %d, %x\n", portName.data(), portID, snd_seq_port_info_get_capability(portInfo));

            if ((caps & SND_SEQ_PORT_CAP_SUBS_READ) != 0)
                entity->endpoints.emplace_back(std::make_unique<MidiEndpoint>(*entity, portName, portID, true));

            if ((caps & SND_SEQ_PORT_CAP_SUBS_WRITE) != 0)
                entity->endpoints.emplace_back(std::make_unique<MidiEndpoint>(*entity, portName, portID, false));
        }
    }

    entities.push_back(std::move(entity));
}

//======================================================================================================================
MidiPort::MidiPort(MidiClient& clnt, bool isInput, std::string_view name, MIDIReadProc rp, void* rc)
        : client(clnt),
          readProc(rp),
          refCon(rc)
{
    // TODO: What does this mean?
    bool enableSubscription = true;

    const unsigned int caps = isInput ? (SND_SEQ_PORT_CAP_WRITE |
                                         (enableSubscription ? SND_SEQ_PORT_CAP_SUBS_WRITE : 0))
                                      : (SND_SEQ_PORT_CAP_READ |
                                         (enableSubscription ? SND_SEQ_PORT_CAP_SUBS_READ : 0));

    portId = snd_seq_create_simple_port(client.handle, name.data(), caps, SND_SEQ_PORT_TYPE_MIDI_GENERIC | SND_SEQ_PORT_TYPE_APPLICATION);
    assert(portId >= 0);
}

MidiPort::~MidiPort()
{
    if (portId >= 0)
        EXPECT_OK(snd_seq_delete_simple_port(client.handle, portId));
}

//======================================================================================================================
OSStatus AlsaMidi::createClient(CFStringRef name, MIDINotifyProc notifyProc, void* notifyRefCon, MIDIClientRef* outClient)
{
    *outClient = getInstance().clients.emplace_back(std::make_unique<MidiClient>(CFStringGetCStringPtr(name, kCFStringEncodingUTF8), notifyProc, notifyRefCon))->getRef();

    return noErr;
}

OSStatus AlsaMidi::disposeClient(MIDIClientRef client)
{
    auto& clients = getInstance().clients;

    const auto it = std::find_if(clients.begin(), clients.end(), [&](const auto& cl) { return cl->getRef() == client; });

    if (it != clients.end())
    {
        clients.erase(it);
        return noErr;
    }

    return kMIDIObjectNotFound;
}

ItemCount AlsaMidi::getNumberOfSources() { return getNumIO(true).first; }

ItemCount AlsaMidi::getNumberOfDestinations() { return getNumIO(false).first; }

MIDIEndpointRef AlsaMidi::getSource(ItemCount idx) { return getNumIO(true, idx).second; }

MIDIEndpointRef AlsaMidi::getDestination(ItemCount idx) { return getNumIO(false, idx).second; }

void AlsaMidi::enumerate()
{
    // TODO: Lock?

    snd_seq_system_info_t* systemInfo = nullptr;
    snd_seq_client_info_t* clientInfo = nullptr;

    snd_seq_system_info_alloca (&systemInfo);
    assert (systemInfo != nullptr);

    std::vector<std::string> prevIds(devices.size());
    std::transform(devices.begin(), devices.end(), prevIds.begin(), [](const auto& kp) { return kp.first; });

    std::vector<std::string> currentIds{};

    snd_seq_t* handle = nullptr;
    if (snd_seq_open(&handle, "default", SND_SEQ_OPEN_DUPLEX, 0) >= 0)
    {
        EXPECT_OK(snd_seq_nonblock(handle, SND_SEQ_NONBLOCK));

        if (snd_seq_system_info(handle, systemInfo) == 0)
        {
            snd_seq_client_info_alloca (&clientInfo);
            assert(clientInfo != nullptr);

            for (int c = 0; c < snd_seq_system_info_get_cur_clients(systemInfo); ++c)
            {
                if (snd_seq_query_next_client(handle, clientInfo) == 0)
                {
                    const char* clientName = snd_seq_client_info_get_name(clientInfo);
                    const int pid      = snd_seq_client_info_get_pid(clientInfo);
                    const int card     = snd_seq_client_info_get_card(clientInfo);
                    auto      numPorts = snd_seq_client_info_get_num_ports(clientInfo);
                    printf("client: %s, pid: %d, card: %d, num ports: %d\n", clientName, pid, card, numPorts);

                    const auto id = [&]
                    {
                        if (card >= 0)
                        {
                            // The long name of the card should be unique, empty string if card is corrupt (e.g. device just removed)
                            char* str = nullptr;
                            return std::string(snd_card_get_longname(card, &str) >= 0 ? str : "");
                        }
                        else
                        {
                            // Probably a virtual port/client
                            return std::string(clientName);
                        }
                    }();

                    if (!id.empty())
                    {
                        currentIds.push_back(id);

                        if (const auto it = devices.find(id); it == devices.end())
                            devices.insert({id, std::make_unique<MidiDevice>(handle, clientInfo)});
                    }
                }
            }
        }

        if (int ret = snd_seq_close(handle); ret < 0)
        {
            printf("Failed to close handle %p: %s (%d)\n", handle, snd_strerror(ret), ret);
        }
    }

    for (const auto& id: prevIds)
        if (std::find(currentIds.begin(), currentIds.end(), id) == currentIds.end())
            devices.erase(id);
}

std::pair<ItemCount, MIDIEndpointRef> AlsaMidi::getNumIO(bool wantsInput, std::optional<ItemCount> ioToSelect)
{
    auto& inst = getInstance();
    inst.enumerate();

    int             num         = 0;
    MIDIEndpointRef refToReturn = NULL;

    for (const auto& [_, device]: inst.devices)
    {
        for (const auto& e: device->entities)
        {
            for (const auto& endp: e->endpoints)
            {
                if (num == ioToSelect)
                    refToReturn = static_cast<MIDIEndpointRef>(endp->getRef());

                num += ((endp->isInput && wantsInput) || (!endp->isInput && !wantsInput)) ? 1 : 0;
            }
        }
    }

    return std::make_pair(num, refToReturn);
}
