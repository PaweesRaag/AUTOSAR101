#ifndef AUTOSAR101_CAN_STACK_H
#define AUTOSAR101_CAN_STACK_H

#include "CanDrv.h"
#include "CanIf.h"

namespace CanStack
{

inline void Transmit(const CanIf::CanFrame& frame)
{
    CanIf::Transmit(frame);
    CanDrv::Write(frame);
}

inline bool Receive(CanIf::CanFrame& frame)
{
    const bool received = CanDrv::Read(frame);
    if (!received)
    {
        return false;
    }

    CanIf::lastFrame = frame;
    return true;
}

} // namespace CanStack

#endif
