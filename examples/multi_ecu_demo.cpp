#include <iostream>

#include "CanDrv.h"
#include "CanIf.h"
#include "PduR.h"
#include "VehicleSignals.h"

namespace
{
CanIf::CanFrame makeSeatSwitchFrame(bool enabled)
{
    return CanIf::CanFrame{
        VehicleSignals::kSeatSwitchCanId,
        enabled
    };
}
}

int main()
{
    std::cout << "=== AUTOSAR101 Multi-ECU Demo ===\n";
    std::cout << "[ECU_A] SeatSwitchSWC -> RTE -> COM -> PduR -> CanIf -> CanDrv\n";

    const CanIf::CanFrame txFrame = makeSeatSwitchFrame(true);

    PduR::RouteComToLower(txFrame.switchState);
    const CanIf::CanFrame routedFrame{
        txFrame.id,
        PduR::RouteLowerToCom()
    };

    CanIf::Transmit(routedFrame);
    CanDrv::Write(routedFrame);

    std::cout << "[CAN ] TX ID=0x" << std::hex << routedFrame.id
              << std::dec << " SeatSwitch=" << routedFrame.switchState << '\n';

    CanIf::CanFrame rxFrame{};
    if (!CanDrv::Read(rxFrame))
    {
        std::cerr << "[ECU_B] No CAN frame received\n";
        return 1;
    }

    std::cout << "[ECU_B] CanIf received ID=0x" << std::hex
              << rxFrame.id << std::dec << '\n';

    std::cout << "[ECU_B] SeatHeatingSWC -> Heater="
              << rxFrame.switchState << " LED="
              << rxFrame.switchState << '\n';

    return 0;
}
