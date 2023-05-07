cmake_minimum_required(VERSION 3.0.0)
project(mcp2515firmata VERSION 1.0.0 DESCRIPTION "Remote Wiring allows you to control an Arduino clone* from a Linux or MacOS machine using the Wiring interface")

#include(CTest)
#enable_testing()

add_library(mcp2515firmata SHARED
    src/mcp2515.cpp
    src/SPI.cpp
)

target_include_directories(mcp2515firmata PRIVATE ${CMAKE_SOURCE_DIR}/src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
