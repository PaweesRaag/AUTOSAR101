#include "PduR.h"
#include "../CanIf/CanIf.h"

namespace PduR {
void routeToCan(const Pdu& pdu) {
    CanIf::CanFrame frame{pdu.id, pdu.data, pdu.length};
    CanIf::transmit(frame);
}
bool routeFromCan(Pdu& pdu) {
    CanIf::CanFrame frame{};
    if (!CanIf::receive(frame)) return false;
    pdu.id = frame.id;
    pdu.data = frame.data;
    pdu.length = frame.length;
    return true;
}
}