#ifndef AUTOSAR101_VEHICLE_SIGNALS_H
#define AUTOSAR101_VEHICLE_SIGNALS_H

#include <cstdint>

namespace VehicleSignals
{

using SeatSwitchState = bool;
using CanId = std::uint32_t;

constexpr CanId kSeatSwitchCanId = 0x101U;

struct SeatCommand
{
    SeatSwitchState enabled{};
};

} // namespace VehicleSignals

#endif
