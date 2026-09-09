#ifndef AUTOSAR101_CANIF_H
#define AUTOSAR101_CANIF_H

#include <cstdint>

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

} // namespace CanIf

#endif
