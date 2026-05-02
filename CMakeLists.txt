cmake_minimum_required(VERSION 4.2)
project(MinecraftServerProtocolCPP)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_SCAN_FOR_MODULES ON)

# TODO: Update version when you can.
find_package(Boost 1.88.0 REQUIRED COMPONENTS system)
find_package(PkgConfig REQUIRED)

pkg_check_modules(SODIUM REQUIRED libsodium)

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
        src/modules/io/codecs/packetcodecs/base/PacketCodec.ixx
        src/modules/io/streams/outputstream/TypedOutputStream.ixx
        src/modules/io/streams/inputstream/TypedInputStream.ixx
        src/modules/utils/EndiannessUtils.ixx
        src/modules/utils/EndiannessUtils.cpp
        src/modules/io/codecs/packetcodecs/VarIntPacketCodec.ixx
        "src/modules/io/codecs/packetcodecs/VarIntPacketCodec.cpp"
        src/modules/io/codecs/packetcodecs/base/PacketCodec.cpp
        src/modules/io/streams/inputstream/TypedInputStream.cpp
        src/modules/io/streams/outputstream/TypedOutputStream.cpp
        src/modules/exceptions/CodecParsingException.ixx
        src/modules/exceptions/CodecParsingException.cpp
        src/modules/utils/enums/Phase.ixx
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
        src/modules/types/GameProfile.ixx
        src/modules/types/UUID.ixx
        src/modules/types/Property.ixx
        src/modules/io/codecs/packetcodecs/PrefixedOptionalPacketCodec.ixx
        src/modules/io/codecs/packetcodecs/PrefixedOptionalPacketCodec.cpp
        src/modules/utils/Base64Utils.ixx
        src/modules/utils/Base64Utils.cpp
        src/modules/io/codecs/packetcodecs/StringPacketCodec.ixx
        src/modules/io/codecs/packetcodecs/UUIDPacketCodec.ixx
        src/modules/io/codecs/packetcodecs/StringPacketCodec.cpp
        src/modules/io/codecs/packetcodecs/UUIDPacketCodec.cpp
        src/modules/utils/RandUtils.ixx
        src/modules/utils/RandUtils.cpp
        src/modules/io/codecs/packetcodecs/PrefixedArrayPacketCodec.ixx
        src/modules/io/codecs/packetcodecs/PrefixedArrayPacketCodec.cpp
        src/modules/io/codecs/packetcodecs/PacketCodecs.ixx
        src/modules/io/codecs/packetcodecs/PacketCodecs.cpp
        src/modules/utils/Concepts.ixx
        src/modules/utils/Concepts.cpp
        src/modules/io/codecs/packetcodecs/GameProfilePacketCodec.ixx
        src/modules/io/codecs/packetcodecs/GameProfilePacketCodec.cpp
        src/modules/io/codecs/packetcodecs/PropertyPacketCodec.ixx
        src/modules/io/codecs/packetcodecs/PropertyPacketCodec.cpp
        src/modules/networking/packet/packettypes/c2s/login/C2SLoginStartPacketType.ixx
        src/modules/networking/packet/packettypes/c2s/login/C2SLoginStartPacketType.cpp
        src/modules/networking/packet/packets/c2s/login/C2SLoginStartPacket.ixx
        src/modules/networking/packet/packets/c2s/login/C2SLoginStartPacket.cpp
        src/modules/types/UUID.cpp
        src/modules/networking/packet/packettypes/c2s/configuration/C2SClientInformationPacketType.ixx
        src/modules/networking/packet/packettypes/c2s/configuration/C2SClientInformationPacketType.cpp
        src/modules/networking/packet/packets/c2s/configuration/C2SClientInformationPacket.ixx
        src/modules/networking/packet/packets/c2s/configuration/C2SClientInformationPacket.cpp
        src/modules/utils/enums/ChatMode.ixx
        src/modules/utils/enums/MainHand.ixx
        src/modules/utils/enums/ParticleStatus.ixx
        src/modules/utils/enums/DisplayedSkinParts.ixx
        src/modules/exceptions/PacketParsingException.ixx
        src/modules/exceptions/PacketParsingException.cpp
        src/modules/exceptions/IOException.ixx
        src/modules/exceptions/IOException.cpp
        src/modules/exceptions/IOStreamException.ixx
        src/modules/exceptions/IOStreamException.cpp
        src/modules/types/Identifier.ixx
        src/modules/types/Identifier.cpp
        src/modules/networking/packet/packettypes/c2s/configuration/C2SCustomPayloadPacketType.cpp
        src/modules/networking/packet/packettypes/c2s/configuration/C2SCustomPayloadPacketType.ixx
        src/modules/networking/packet/packets/c2s/configuration/C2SCustomPayloadPacket.ixx
        src/modules/networking/packet/packets/c2s/configuration/C2SCustomPayloadPacket.cpp
        src/modules/io/codecs/packetcodecs/IdentifierPacketCodec.ixx
        src/modules/io/codecs/packetcodecs/IdentifierPacketCodec.cpp
        src/modules/networking/packet/packettypes/c2s/configuration/C2SFinishConfigurationPacketType.ixx
        src/modules/networking/packet/packettypes/c2s/configuration/C2SFinishConfigurationPacketType.cpp
        src/modules/networking/packet/packets/c2s/configuration/C2SFinishConfigurationPacket.cpp
)

add_executable(MinecraftServerProtocolCPPTests
        test/sources/main.cpp)

target_sources(
        MinecraftServerProtocolCPP
        PUBLIC
        FILE_SET CXX_MODULES FILES ${MODULE_INTERFACES}
)

target_include_directories(MinecraftServerProtocolCPP PUBLIC src/headers
        ${Boost_INCLUDE_DIRS} ${SODIUM_INCLUDE_DIRS})
target_include_directories(MinecraftServerProtocolCPPTests PRIVATE test/headers)

target_link_libraries(MinecraftServerProtocolCPP PRIVATE Boost::system
        ${SODIUM_LIBRARIES})
target_link_libraries(MinecraftServerProtocolCPPTests PRIVATE MinecraftServerProtocolCPP)