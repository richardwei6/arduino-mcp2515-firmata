cmake_minimum_required(VERSION 3.0.0)
project(mcp2515firmata VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(mcp2515firmata mcp2515firmata.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
