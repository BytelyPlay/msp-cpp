cmake_minimum_required(VERSION 4.2)
project(MinecraftServerProtocolCPP)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_SCAN_FOR_MODULES ON)

# TODO: Update version when you can.
find_package(Boost 1.88.0 REQUIRED COMPONENTS system)
find_package(OpenSSL 3.5.3 REQUIRED)

file(GLOB_RECURSE MODULE_INTERFACES
        "src/modules/*.ixx"
)

add_library(MinecraftServerProtocolCPP STATIC
        src/modules/networking/MinecraftProtocol.cpp
        src/modules/networking/MinecraftProtocol.ixx
        src/modules/utils/Logger.ixx
        src/modules/utils/Logger.cpp
        src/modules/networking/MinecraftServer.ixx
        src/modules/networking/MinecraftServer.cpp
        src/modules/networking/MinecraftClient.ixx
        src/modules/networking/MinecraftClient.cpp
        src/headers/BoostNamespaces.hpp
        src/modules/networking/packet/Packets.ixx
        src/modules/networking/packet/Packets.cpp
        src/modules/networking/packet/packets/base/Packet.ixx
        src/modules/networking/packet/packets/base/Packet.cpp
        src/modules/networking/packet/packettypes/base/PacketType.ixx
        src/modules/networking/packet/packettypes/base/PacketType.cpp
        src/modules/networking/packet/packettypes/c2s/base/PacketTypeC2S.ixx
        src/modules/networking/packet/packettypes/s2c/base/PacketTypeS2C.ixx
        src/modules/networking/packet/packettypes/c2s/base/PacketTypeC2S.cpp
        src/modules/networking/packet/packettypes/s2c/base/PacketTypeS2C.cpp
        src/modules/networking/packet/packets/c2s/base/PacketC2S.ixx
        src/modules/networking/packet/packets/s2c/base/PacketS2C.ixx
        src/modules/io/codecs/base/Codec.ixx
        src/modules/io/streams/outputstream/TypedOutputStream.ixx
        src/modules/io/streams/inputstream/TypedInputStream.ixx
        src/modules/utils/EndiannessUtils.ixx
        src/modules/utils/EndiannessUtils.cpp
        src/modules/io/codecs/VarIntCodec.ixx
        "src/modules/io/codecs/VarIntCodec.cpp"
        src/modules/io/codecs/base/Codec.cpp
        src/modules/io/streams/inputstream/TypedInputStream.cpp
        src/modules/io/streams/outputstream/TypedOutputStream.cpp
        src/modules/io/codecs/base/BasicCodec.ixx
        src/modules/exceptions/CodecParsingException.ixx
        src/modules/exceptions/CodecParsingException.cpp
        src/modules/networking/Phases.ixx
        src/modules/networking/packet/packettypes/c2s/handshake/C2SIntentionPacketType.ixx
        src/modules/networking/packet/packettypes/c2s/handshake/C2SIntentionPacketType.cpp
        src/modules/networking/packet/packets/c2s/handshake/C2SIntentionPacket.ixx
        src/modules/networking/packet/packets/c2s/handshake/C2SIntentionPacket.cpp
        src/modules/networking/packet/packets/c2s/base/PacketC2S.cpp
        src/modules/io/memory/CustomMemoryArena.ixx
        src/modules/io/memory/CustomMemoryArena.cpp
        src/modules/networking/packet/packettypes/s2c/login/S2CLoginFinishedPacketType.ixx
        src/modules/networking/packet/packettypes/s2c/login/S2CLoginFinishedPacketType.cpp
        src/modules/networking/packet/packets/s2c/login/S2CLoginFinishedPacket.ixx
        src/modules/networking/packet/packets/s2c/login/S2CLoginFinishedPacket.cpp
        src/modules/io/codecs/GameProfileCodec.ixx
        src/modules/io/codecs/GameProfileCodec.cpp
        src/modules/types/GameProfile.ixx
        src/modules/types/UUID.ixx
        src/modules/types/Property.ixx
        src/modules/io/codecs/PrefixedOptionalCodec.ixx
        src/modules/io/codecs/PrefixedOptionalCodec.cpp
)

add_executable(MinecraftServerProtocolCPPTests
        test/sources/main.cpp)

target_sources(
        MinecraftServerProtocolCPP
        PUBLIC
        FILE_SET CXX_MODULES FILES ${MODULE_INTERFACES}
)

target_include_directories(MinecraftServerProtocolCPP PUBLIC src/headers ${Boost_INCLUDE_DIRS})
target_include_directories(MinecraftServerProtocolCPPTests PRIVATE test/headers)

target_link_libraries(MinecraftServerProtocolCPP PRIVATE Boost::system OpenSSL::SSL)
target_link_libraries(MinecraftServerProtocolCPPTests PRIVATE MinecraftServerProtocolCPP)