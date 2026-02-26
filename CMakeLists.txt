cmake_minimum_required(VERSION 4.2)
project(MinecraftServerProtocolCPP)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_SCAN_FOR_MODULES ON)

# TODO: Update version when you can.
find_package(Boost 1.88.0 REQUIRED COMPONENTS system)

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
        src/headers/Types.hpp
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
        src/modules/io/streams/inputstream/FlexibleStreamBuf.ixx
        src/modules/io/streams/inputstream/FlexibleStreamBuf.cpp
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

target_link_libraries(MinecraftServerProtocolCPP PRIVATE Boost::system)
target_link_libraries(MinecraftServerProtocolCPPTests PRIVATE MinecraftServerProtocolCPP)