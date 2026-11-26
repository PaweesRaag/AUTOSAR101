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
       COM       Signals -> PDU payload
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
       COM       PDU payload -> Signals
        |
       RTE
        |
ECU B receiving SWC
```

Each ECU owns its own RTE instance. The simulated bus is the only shared
transport between the two ECU sides; this avoids the false assumption that
separate executable processes share a C++ static variable.

## Module responsibilities

- **RTE**: stores and exposes a typed vehicle-status sample local to an ECU.
- **COM**: serializes vehicle speed and engine speed as two unsigned 16-bit
  big-endian signals. Speed occupies bytes 0–1; engine RPM occupies bytes 2–3.
  The exact four-byte payload length and PDU identifier are checked on receive.
- **PduR**: maps the configured PDU identifier to/from CAN identifier 0x120 and
  rejects unknown identifiers or payload lengths beyond classic CAN's limit.
- **CanIf**: validates the classic CAN payload length and delegates transport.
- **CanBus**: deterministic FIFO queue used to model message transfer.
- **Application**: demonstrates sender and receiver ECU flows.

## Vehicle-status PDU layout

| Byte offset | Width | Signal | Encoding |
|---|---:|---|---|
| 0–1 | 16 bits | Vehicle speed (km/h) | Unsigned, big-endian |
| 2–3 | 16 bits | Engine speed (rpm) | Unsigned, big-endian |

PDU ID: `0x0001`; CAN ID: `0x120`; payload length: 4 bytes.

## Deliberate simplifications

The model uses one vehicle-status PDU, one CAN ID and classic CAN's eight-byte
maximum payload. It does not implement generated configuration, signal
endianness variants, update bits, deadline monitoring, transmission modes,
PDU groups, configurable routing tables, CAN arbitration, bit timing, CRC, ACK,
error frames, interrupts, controller registers, transceiver control, OS
scheduling, or hardware faults. A real AUTOSAR COM/PduR/CanIf/CanDrv integration
is configuration-driven and substantially more complex.

## Build and run

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/autosar101_demo
```
