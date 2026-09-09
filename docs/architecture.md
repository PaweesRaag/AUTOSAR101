# AUTOSAR101 Architecture

AUTOSAR101 is an educational C++ simulation of selected AUTOSAR Classic concepts. The implementation deliberately uses lightweight abstractions instead of claiming production AUTOSAR conformance.

## Current Direction

```text
                  ECU A
┌─────────────────────────────────────┐
│ Seat Switch SWC                    │
│        │                            │
│        ▼                            │
│       RTE                           │
│        │                            │
│       COM                           │
│        │                            │
│      PduR                           │
│        │                            │
│     CanIf                           │
└────────┼────────────────────────────┘
         │
         │        Simulated CAN Bus
         │
┌────────┼────────────────────────────┐
│      CanIf                          │
│        │                             │
│      PduR                            │
│        │                             │
│       COM                            │
│        │                             │
│       RTE                            │
│        │                             │
│ Seat Heating SWC                    │
│        │                             │
│   Heater / LED                      │
└─────────────────────────────────────┘
                  ECU B
```

## Layer Responsibilities

- **SWC**: application behavior and runnables.
- **RTE**: generated-style communication API boundary used by SWCs.
- **COM**: signal packing/unpacking and PDU-facing abstraction.
- **PduR**: planned routing boundary between upper and lower communication modules.
- **CanIf**: planned CAN hardware abstraction boundary.
- **CAN simulator**: deterministic transport used for desktop execution and tests.

## Security Extension

A later milestone adds SecOC-style message authentication and freshness validation:

```text
Application signal
       +
Freshness value
       ↓
Authentication / CMAC
       ↓
CAN PDU
       ↓
Receiver validation
       ↓
Accept / Reject
```

## Scope

The project is a learning/reference implementation. It does not replace an AUTOSAR generator, vendor BSW, ECU configuration tools, or certified automotive software.