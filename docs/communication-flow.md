# Multi-ECU Communication Flow

This milestone models a simplified Classic AUTOSAR communication path.

```text
ECU A
SeatSwitchSWC
      |
      v
     COM
      |
      v
    PduR
      |
      v
   CanIf
      |
      v
     CAN
      |
      | simulated CAN bus
      v
     CAN
      |
      v
   CanIf
      |
      v
    PduR
      |
      v
     COM
      |
      v
ECU B
SeatHeatingSWC
```

The `SeatSwitch` application signal is packed into one byte of a simulated CAN frame using CAN ID `0x101`.

This is an educational simulator. It mirrors architectural boundaries for learning and testing; it is not a production AUTOSAR-conformant implementation.