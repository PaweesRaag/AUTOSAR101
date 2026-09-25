#include "Com.h"

namespace {
constexpr unsigned kSeatSwitchCanId = 0x101U;
}

namespace Com {
void transmitSeatSwitch(const SeatSwitchSignal& signal) {
    PduR::Pdu pdu{};
    pdu.id = kSeatSwitchCanId;
    pdu.data[0] = signal.enabled ? 1U : 0U;
    pdu.length = 1U;
    PduR::routeToCan(pdu);
}
bool receiveSeatSwitch(SeatSwitchSignal& signal) {
    PduR::Pdu pdu{};
    if (!PduR::routeFromCan(pdu) || pdu.id != kSeatSwitchCanId || pdu.length < 1U) {
        return false;
    }
    signal.enabled = pdu.data[0] != 0U;
    return true;
}
}