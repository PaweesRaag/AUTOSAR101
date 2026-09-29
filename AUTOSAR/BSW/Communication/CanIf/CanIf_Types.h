#pragma once
#include <array>
#include <cstdint>

namespace CanIf {
struct CanFrame {
    std::uint32_t id{};
    std::array<std::uint8_t, 8> data{};
    std::uint8_t length{};
};
}