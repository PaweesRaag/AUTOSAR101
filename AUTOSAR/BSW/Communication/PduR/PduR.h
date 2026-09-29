#pragma once
#include "../CanIf/CanIf_Types.h"
#include <array>
#include <cstdint>

namespace PduR {
struct Pdu {
    std::uint32_t id{};
    std::array<std::uint8_t, 8> data{};
    std::uint8_t length{};
};
void routeToCan(const Pdu& pdu);
bool routeFromCan(Pdu& pdu);
}