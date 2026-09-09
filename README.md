# AUTOSAR101

> A hands-on educational implementation of selected AUTOSAR Classic concepts in C++ — evolving from SWC/RTE communication toward multi-ECU communication, diagnostics, and automotive cybersecurity.

![AUTOSAR Architecture](https://github.com/user-attachments/assets/6c99a91d-0257-41d3-81c5-4027bc8cc6db)

## What is this?

AUTOSAR101 is a from-scratch learning project that models selected AUTOSAR Classic software concepts with small, runnable C++ components.

The goal is not to reproduce a production AUTOSAR stack. The goal is to make the architecture concrete by implementing interfaces, data flow, simulated ECUs, communication boundaries, and tests that can be inspected and executed on a desktop system.

## Current Focus

```text
Application / SWCs
        ↓
       RTE
        ↓
       COM
        ↓
      PduR
        ↓
     CanIf
        ↓
  Simulated CAN
        ↓
     CanIf
        ↓
      PduR
        ↓
       COM
        ↓
       RTE
        ↓
Application / SWCs
```

The current codebase already contains early SWC, port, RTE, and COM experiments. The repository is being progressively refactored into the architecture above.

## Planned Feature Set

| Area | Status |
|---|---|
| AUTOSAR layered concepts | 🟢 Foundation |
| Software Components (SWCs) | 🟢 Started |
| P-Port / R-Port concepts | 🟢 Started |
| RTE communication APIs | 🟢 Started |
| COM / PDU abstraction | 🟡 Started |
| PduR routing | 🟡 Planned |
| CanIf / CAN simulation | 🟡 Planned |
| Multi-ECU end-to-end demo | 🟡 Planned |
| UDS / DCM / DEM | 🟡 Planned |
| SecOC / freshness | 🟡 Planned |
| Crypto / AES-CMAC adapter | 🟡 Planned |
| NvM / memory stack | ⚪ Optional |
| CI + unit tests | 🟡 Planned |

## Example Use Case

The main learning scenario is a simulated automotive seat-heating system:

```text
Seat Switch SWC (ECU A)
          ↓
         RTE
          ↓
         COM
          ↓
        CAN
          ↓
         COM
          ↓
         RTE
          ↓
Seat Heating SWC (ECU B)
          ↓
   Heater + Status LED
```

## Repository Layout

```text
AUTOSAR101/
├── AUTOSAR/             # Current learning implementations
│   ├── ECU_A/            # Sender-side ECU experiments
│   ├── ECU_B/            # Receiver-side ECU experiments
│   └── shared/           # Shared communication abstractions
├── docs/
│   ├── architecture.md  # System/data-flow diagrams
│   ├── roadmap.md       # Implementation roadmap
│   └── learning-journal.md
└── README.md
```

## Engineering Principles

- Prefer explicit interfaces over shared state.
- Keep application logic independent from transport details.
- Make data flow observable through deterministic demo logs.
- Add tests as each stack component becomes stable.
- Clearly distinguish simplified educational behavior from production AUTOSAR behavior.

## Status

This repository is actively being developed. Existing files contain exploratory implementations; the roadmap documents the intended target architecture.

## Documentation

- [Architecture](docs/architecture.md)
- [Implementation Roadmap](docs/roadmap.md)
- [Learning Journal](docs/learning-journal.md)

## Disclaimer

This is an educational implementation. It is not production AUTOSAR software, does not claim AUTOSAR conformance, and is not intended for deployment in safety-critical or road-going systems.