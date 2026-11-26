#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace autosar101 {

constexpr std::size_t kCanMaxPayload = 8;

struct SignalFrame {
    std::uint16_t vehicle_speed_kmh{0};
};

struct Pdu {
    std::uint16_t pdu_id{0};
    std::array<std::uint8_t, kCanMaxPayload> payload{};
    std::uint8_t length{0};
};

struct CanFrame {
    std::uint16_t can_id{0};
    std::array<std::uint8_t, kCanMaxPayload> data{};
    std::uint8_t dlc{0};
};

} // namespace autosar101
