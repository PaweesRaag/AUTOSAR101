# RTE, Ports and Interfaces

AUTOSAR101 now models the application-to-BSW boundary through an educational RTE layer.

## Sender/Receiver communication

- ECU_A SeatSwitchSWC acts as the sender.
- ECU_B SeatHeatingSWC acts as the receiver.
- The SeatSwitch value is the communicated data element.
- The RTE exposes application-facing APIs while the communication stack remains below it.

## Application boundary

```text
SeatSwitchSWC
    |
    +-- RTE write
    |
    +-- COM -> PduR -> CanIf -> CAN simulator
                              |
                              +-- CanIf -> PduR -> COM
                                                      |
                                                      +-- RTE read
                                                            |
                                                       SeatHeatingSWC
```

The SWCs no longer include COM, PduR, CanIf, or CAN headers directly.

## Port concept

Conceptually, the sender exposes a P-Port through the RTE and the receiver consumes the data through an R-Port. This repository uses generated-style C++ APIs to demonstrate the boundary; real AUTOSAR RTEs are generated from ECU/SWC configuration.

This is an educational approximation, not a production AUTOSAR-conformant RTE.
