# AUTOSAR101 roadmap

## Implemented in the current simulator

- ECU-local typed RTE sample storage
- COM packing/unpacking for a 16-bit vehicle-speed signal
- PDU identifier and payload representation
- PduR mapping between one configured PDU and CAN ID 0x120
- CanIf payload-length validation
- Deterministic in-process CAN transport queue
- Two-ECU end-to-end demonstration
- Unit/integration tests and CMake/CTest build

## Next engineering milestones

1. **Configuration-driven COM**: multiple signals, bit positions, lengths,
   signedness, scaling, endianness and bounds checking.
2. **PDU routing configuration**: multiple PDU IDs, destinations and
   rejection/error counters.
3. **CAN semantics**: standard/extended identifiers, frame-type checks,
   bus-off/error-state simulation and deterministic fault injection.
4. **RTE semantics**: explicit sender-receiver interfaces, data validity,
   queued vs unqueued communication and client-server calls.
5. **Diagnostics**: a small UDS subset through a DCM-like request dispatcher,
   with negative response codes and DEM event storage.
6. **Security**: a clearly separated SecOC teaching model with freshness
   handling and a vetted cryptographic library backend (never custom crypto).
7. **Embedded target**: replace the simulated CanIf/CanBus boundary with a
   target-specific driver only after selecting an MCU and toolchain.

## Definition of done for a milestone

- Interfaces and module responsibilities are documented.
- Normal and malformed inputs are tested.
- Build succeeds with warnings enabled.
- Demo output is reproducible.
- Limitations are explicit; no physical or AUTOSAR-compliance claims are made.
