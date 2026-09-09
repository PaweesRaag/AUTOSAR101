#include <iostream>

#include "CanStack.h"
#include "PduR.h"
#include "VehicleSignals.h"

int main()
{
    using VehicleSignals::kSeatSwitchCanId;

    std::cout << "=== AUTOSAR101 Multi-ECU Demo ===\n";
    std::cout << "[ECU_A] SeatSwitchSWC -> RTE -> COM -> PduR -> CanIf -> CanDrv\n";

    const bool switchState = true;

    CanIf::CanFrame txFrame{
        kSeatSwitchCanId,
        switchState
    };

    PduR::RouteTransmit(txFrame.switchState);
    const bool routedSignal = PduR::RouteReceive();

    txFrame.switchState = routedSignal;
    CanStack::Transmit(txFrame);

    std::cout << "[CAN ] TX ID=0x" << std::hex << txFrame.id
              << std::dec << " SeatSwitch=" << txFrame.switchState << '\n';

    CanIf::CanFrame rxFrame{};
    if (!CanStack::Receive(rxFrame))
    {
        std::cerr << "[ECU_B] No CAN frame received\n";
        return 1;
    }

    std::cout << "[ECU_B] RX ID=0x" << std::hex << rxFrame.id
              << std::dec << " SeatSwitch=" << rxFrame.switchState << '\n';
    std::cout << "[ECU_B] SeatHeatingSWC -> Heater="
              << rxFrame.switchState << " LED="
              << rxFrame.switchState << '\n';

    return 0;
}
