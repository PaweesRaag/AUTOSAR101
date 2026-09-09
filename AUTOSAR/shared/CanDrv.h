#ifndef AUTOSAR101_CAN_DRV_H
#define AUTOSAR101_CAN_DRV_H

#include "CanBusSimulator.h"

namespace CanDrv
{

inline void Write(const CanIf::CanFrame& frame)
{
    CanBusSimulator::Publish(frame);
}

inline bool Read(CanIf::CanFrame& frame)
{
    return CanBusSimulator::Consume(frame);
}

} // namespace CanDrv

#endif
