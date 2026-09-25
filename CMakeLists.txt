cmake_minimum_required(VERSION 3.16)
project(AUTOSAR101 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(AUTOSAR101_SOURCES
    AUTOSAR/BSW/Communication/Can/Can.cpp
    AUTOSAR/BSW/Communication/Can/CanBusSimulator.cpp
    AUTOSAR/BSW/Communication/CanIf/CanIf.cpp
    AUTOSAR/BSW/Communication/PduR/PduR.cpp
    AUTOSAR/BSW/Communication/Com/Com.cpp
    AUTOSAR/ECU_A/SWC/SeatSwitchSWC.cpp
    AUTOSAR/ECU_B/SWC/SeatHeatingSWC.cpp
)

add_executable(multi_ecu_seat_heating examples/multi_ecu_seat_heating.cpp ${AUTOSAR101_SOURCES})
target_include_directories(multi_ecu_seat_heating PRIVATE AUTOSAR)

add_executable(test_multi_ecu tests/test_multi_ecu.cpp ${AUTOSAR101_SOURCES})
target_include_directories(test_multi_ecu PRIVATE AUTOSAR)

enable_testing()
add_test(NAME multi_ecu_communication COMMAND test_multi_ecu)

if (MSVC)
  target_compile_options(multi_ecu_seat_heating PRIVATE /W4 /WX)
  target_compile_options(test_multi_ecu PRIVATE /W4 /WX)
else()
  target_compile_options(multi_ecu_seat_heating PRIVATE -Wall -Wextra -Wpedantic -Werror)
  target_compile_options(test_multi_ecu PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()