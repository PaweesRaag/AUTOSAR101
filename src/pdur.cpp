#include "autosar101/pdur.hpp"
#include "autosar101/com.hpp"

namespace autosar101 {

std::optional<CanFrame> PduR::route_to_can(const Pdu& pdu) noexcept {
    if (pdu.pdu_id != Com::kVehicleStatusPduId || pdu.length > kCanMaxPayload) {
        return std::nullopt;
    }

    CanFrame frame{};
    frame.can_id = kVehicleStatusCanId;
    frame.dlc = pdu.length;
    frame.data = pdu.payload;
    return frame;
}

std::optional<Pdu> PduR::route_from_can(const CanFrame& frame) noexcept {
    if (frame.can_id != kVehicleStatusCanId || frame.dlc > kCanMaxPayload) {
        return std::nullopt;
    }

    Pdu pdu{};
    pdu.pdu_id = Com::kVehicleStatusPduId;
    pdu.length = frame.dlc;
    pdu.payload = frame.data;
    return pdu;
}

} // namespace autosar101
