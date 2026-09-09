#ifndef AUTOSAR101_CANIF_H
#define AUTOSAR101_CANIF_H

#include <cstdint>
#include "PduR.h"

namespace CanIf
{

struct CanFrame
{
    std::uint32_t id{};
    bool switchState{};
};

inline CanFrame lastFrame{};

inline void Transmit(const CanFrame& frame)
{
    lastFrame = frame;
}

inline bool Receive(CanFrame& frame)
{
    frame = lastFrame;
    return true;
}

} // namespace CanIf

#endif
