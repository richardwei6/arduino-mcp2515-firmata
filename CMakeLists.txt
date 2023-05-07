cmake_minimum_required(VERSION 3.0.0)
project(mcp2515firmata VERSION 1.0.0 DESCRIPTION "Remote Wiring allows you to control an Arduino clone* from a Linux or MacOS machine using the Wiring interface")
set(CMAKE_OSX_ARCHITECTURES "x86_64")

#include(CTest)
#enable_testing()

add_library(mcp2515firmata SHARED
    src/mcp2515.cpp
    src/SPI.cpp
)

target_include_directories(mcp2515firmata PRIVATE ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/dependencies/include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

find_library (
    LIBFIRMATA
    NAMES firmata libfirmata # what to look for
    HINTS "${CMAKE_SOURCE_DIR}/dependencies/lib" # where to look
    NO_DEFAULT_PATH # do not search system default paths
)

find_library (
    LIBREMOTE_WIRING
    NAMES remote_wiring libremote_wiring # what to look for
    HINTS "${CMAKE_SOURCE_DIR}/dependencies/lib" # where to look
    NO_DEFAULT_PATH # do not search system default paths
)

find_library (
    LIBSERIAL_WIRING
    NAMES serial_wiring libserial_wiring # what to look for
    HINTS "${CMAKE_SOURCE_DIR}/dependencies/lib" # where to look
    NO_DEFAULT_PATH # do not search system default paths
)

message("${CMAKE_SOURCE_DIR}/lib")
message(STATUS "LIBFIRMATA: [${LIBFIRMATA}]")
message(STATUS "LIBREMOTE_WIRING: [${LIBREMOTE_WIRING}]")
message(STATUS "LIBSERIAL_WIRING: [${LIBSERIAL_WIRING}]")


target_link_libraries(mcp2515firmata ${LIBFIRMATA} ${LIBREMOTE_WIRING} ${LIBSERIAL_WIRING})