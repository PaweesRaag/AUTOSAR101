cmake_minimum_required(VERSION 3.16)
project(AUTOSAR101 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

function(autosar101_enable_warnings target)
    if (MSVC)
        target_compile_options(${target} PRIVATE /W4 /WX)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endfunction()

add_executable(autosar101_demo
    examples/multi_ecu_demo.cpp
)

target_include_directories(autosar101_demo PRIVATE
    AUTOSAR/shared
    AUTOSAR/ECU_A
    AUTOSAR/ECU_B
)
autosar101_enable_warnings(autosar101_demo)

add_executable(autosar101_smoke_test
    tests/smoke_test.cpp
)

target_include_directories(autosar101_smoke_test PRIVATE
    AUTOSAR/shared
)
autosar101_enable_warnings(autosar101_smoke_test)

enable_testing()
add_test(NAME communication_smoke_test COMMAND autosar101_smoke_test)
