#include "../AUTOSAR/ECU_A/RTE/Rte_SeatSwitch.h"
#include "../AUTOSAR/ECU_B/RTE/Rte_SeatHeating.h"
#include <cassert>

int main()
{
    bool received{false};

    assert(ECU_B::Rte::readSeatSwitch(received) == false);

    ECU_A::Rte::writeSeatSwitch(true);
    assert(ECU_B::Rte::readSeatSwitch(received));
    assert(received);

    ECU_A::Rte::writeSeatSwitch(false);
    assert(ECU_B::Rte::readSeatSwitch(received));
    assert(!received);

    return 0;
}
