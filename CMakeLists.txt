cmake_minimum_required(VERSION 4.2)
project(MinecraftServerProtocolCPP)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

file(
        GLOB_RECURSE MODULE_INTERFACES
        "src/modules/**/*.ixx"
)

add_library(MinecraftServerProtocolCPP STATIC
        src/modules/MinecraftProtocol.ixx
        src/modules/MinecraftProtocol.cpp
)

add_executable(MinecraftServerProtocolCPPTests
        test/sources/main.cpp)

target_sources(
        MinecraftServerProtocolCPP
        PUBLIC
        FILE_SET CXX_MODULES FILES ${MODULE_INTERFACES}
)

target_include_directories(MinecraftServerProtocolCPP PUBLIC src/headers)
target_include_directories(MinecraftServerProtocolCPPTests PRIVATE test/headers)

target_link_libraries(MinecraftServerProtocolCPPTests PRIVATE MinecraftServerProtocolCPP)
