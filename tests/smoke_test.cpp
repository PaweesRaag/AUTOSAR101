#include <cassert>

#include "CanDrv.h"
#include "CanIf.h"
#include "PduR.h"
#include "VehicleSignals.h"

int main()
{
    constexpr bool expected = true;

    PduR::RouteComToLower(expected);
    const bool routed = PduR::RouteLowerToCom();
    assert(routed == expected);

    const CanIf::CanFrame frame{
        VehicleSignals::kSeatSwitchCanId,
        routed
    };

    CanDrv::Write(frame);

    CanIf::CanFrame received{};
    assert(CanDrv::Read(received));
    assert(received.id == VehicleSignals::kSeatSwitchCanId);
    assert(received.switchState == expected);

    return 0;
}
