#include "Rte_SeatSwitch.h"
#include "../../BSW/Communication/Com/Com.h"

namespace ECU_A::Rte {
void writeSeatSwitch(bool enabled)
{
    Com::transmitSeatSwitch({enabled});
}
}
