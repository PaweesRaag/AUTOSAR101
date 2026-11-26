cmake_minimum_required(VERSION 3.16)
project(AUTOSAR101 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(autosar101
    src/com.cpp
    src/pdur.cpp
    src/can_bus.cpp
    src/can_if.cpp
)
target_include_directories(autosar101 PUBLIC include)
if(MSVC)
    target_compile_options(autosar101 PRIVATE /W4 /WX)
else()
    target_compile_options(autosar101 PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

add_executable(autosar101_demo src/main.cpp)
target_link_libraries(autosar101_demo PRIVATE autosar101)

include(CTest)
if(BUILD_TESTING)
    add_executable(autosar101_tests tests/test_main.cpp)
    target_link_libraries(autosar101_tests PRIVATE autosar101)
    add_test(NAME autosar101_tests COMMAND autosar101_tests)
endif()
