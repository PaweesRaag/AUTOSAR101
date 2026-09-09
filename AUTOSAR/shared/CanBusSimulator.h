#ifndef AUTOSAR101_CAN_BUS_SIMULATOR_H
#define AUTOSAR101_CAN_BUS_SIMULATOR_H

#include "CanIf.h"

namespace CanBusSimulator
{

inline CanIf::CanFrame busFrame{};
inline bool hasFrame = false;

inline void Publish(const CanIf::CanFrame& frame)
{
    busFrame = frame;
    hasFrame = true;
}

inline bool Consume(CanIf::CanFrame& frame)
{
    if (!hasFrame)
    {
        return false;
    }

    frame = busFrame;
    hasFrame = false;
    return true;
}

} // namespace CanBusSimulator

#endif
