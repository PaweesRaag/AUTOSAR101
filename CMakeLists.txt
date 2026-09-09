cmake_minimum_required(VERSION 3.16)
project(AUTOSAR101 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(autosar101_demo
    examples/multi_ecu_demo.cpp
)

target_include_directories(autosar101_demo PRIVATE
    AUTOSAR/shared
    AUTOSAR/ECU_A
    AUTOSAR/ECU_B
)

if (MSVC)
    target_compile_options(autosar101_demo PRIVATE /W4 /WX)
else()
    target_compile_options(autosar101_demo PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
