# AUTOSAR101 implementation architecture

## Scope

This repository is an educational, AUTOSAR Classic-inspired C++ model. It is
not an AUTOSAR-compliant BSW implementation, generated RTE, MCAL, CAN driver,
or production ECU software. The model makes selected responsibility boundaries
executable and testable.

## End-to-end signal path

```text
ECU A application SWC
        |
       RTE
        |
       COM       Signal -> PDU payload
        |
       PduR      PDU ID -> configured CAN ID
        |
      CanIf      hardware-independent interface
        |
   Simulated CAN bus
        |
      CanIf
        |
       PduR      CAN ID -> PDU ID
        |
       COM       PDU payload -> Signal
        |
       RTE
        |
ECU B receiving SWC
```

Each ECU owns its own RTE instance. The simulated bus is the only shared
transport between the two ECU sides; this avoids the false assumption that
separate executable processes share a C++ static variable.

## Module responsibilities

- **RTE**: stores and exposes a typed sender-receiver sample local to an ECU.
- **COM**: packs/unpacks the configured 16-bit vehicle-speed signal in
  big-endian byte order.
- **PduR**: maps the configured PDU identifier to/from CAN identifier 0x120.
- **CanIf**: validates the classic CAN payload length and delegates transport.
- **CanBus**: deterministic FIFO queue used to model message transfer.
- **Application**: demonstrates sender and receiver ECU flows.

## Deliberate simplifications

The model uses one signal, one PDU, one CAN ID and classic CAN's eight-byte
maximum payload. It does not implement generated configuration, signal
endianness variants, update bits, deadline monitoring, transmission modes,
PDU groups, routing tables, CAN arbitration, bit timing, CRC, ACK, error
frames, interrupts, controller registers, transceiver control, OS scheduling,
or hardware faults. A real AUTOSAR COM/PduR/CanIf/CanDrv integration is
configuration-driven and substantially more complex.

## Build and run

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/autosar101_demo
```
