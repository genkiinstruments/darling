project(CoreAudio)

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -stdlib=libc++")

set(coreaudio_sources
	AudioHardware.cpp
    AudioHardwareImpl.cpp
    HostTime.mm
    pulse/AudioHardwareImplPA.cpp
    pulse/AudioHardwareImplPAInput.cpp
    pulse/AudioHardwareImplPAOutput.cpp
    AudioHardwareStream.cpp
    pulse/AudioHardwareStreamPA.cpp
    pulse/AudioHardwareStreamPAInput.cpp
    pulse/AudioHardwareStreamPAOutput.cpp
    pulse/PADispatchMainLoop.cpp

    alsa/AudioHardwareImplALSA.cpp
    alsa/AudioHardwareImplALSAInput.cpp
    alsa/AudioHardwareImplALSAOutput.cpp
	)

add_framework(CoreAudio
	FAT
    CURRENT_VERSION
    VERSION "A"

    SOURCES
        ${coreaudio_sources}

    DEPENDENCIES
        system
        cxx
        CoreFoundation
        pulse
		asound
)
