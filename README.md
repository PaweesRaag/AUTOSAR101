# AUTOSAR101

**A hands-on C++17 learning project exploring Classic AUTOSAR communication concepts through an executable, testable ECU communication-stack simulator.**

AUTOSAR101 began as a collection of notes and small experiments around Software Components (SWCs), ports, the Runtime Environment (RTE), and Basic Software (BSW) communication modules. It now also contains a structured simulator that brings several of those concepts together into one end-to-end communication path.

The goal is to make the relationships between application software, communication services, routing, and hardware abstraction easier to understand by implementing a small model that can be built, executed, inspected, and tested.

> [!IMPORTANT]
> **Project scope:** AUTOSAR101 is an educational, Classic AUTOSAR-inspired simulation. It is **not** an AUTOSAR-compliant stack, production ECU software, an output of an AUTOSAR configuration generator, or a physical CAN implementation. The project models selected concepts and deliberately simplifies many platform-specific behaviours.

---

## Table of contents

- [Project at a glance](#project-at-a-glance)
- [What the simulator demonstrates](#what-the-simulator-demonstrates)
- [End-to-end communication flow](#end-to-end-communication-flow)
- [Current vehicle-status message](#current-vehicle-status-message)
- [Module responsibilities](#module-responsibilities)
- [Build, test, and run](#build-test-and-run)
- [Expected demonstration](#expected-demonstration)
- [Test coverage](#test-coverage)
- [Repository structure](#repository-structure)
- [Original learning material](#original-learning-material)
- [Design decisions and current limitations](#design-decisions-and-current-limitations)
- [Roadmap](#roadmap)
- [Learning objectives](#learning-objectives)
- [Contributing](#contributing)
- [Disclaimer](#disclaimer)

## Project at a glance

| Property | Current implementation |
|---|---|
| Language | C++17 |
| Build system | CMake 3.16+ |
| Communication model | Sender-receiver style signal transfer |
| ECU endpoints | Two logical ECU endpoints in one process |
| Communication path | RTE → COM → PduR → CanIf → simulated bus |
| Signals | Vehicle speed and engine speed |
| PDU | One four-byte vehicle-status PDU |
| CAN identifier | `0x120` |
| Transport | Deterministic in-process FIFO queue |
| Automated checks | CMake build, CTest, demo execution in GitHub Actions |

### Highlights

- A single end-to-end path connects an application-level signal update on ECU A to a signal read on ECU B.
- Communication modules are separated into small interfaces and implementations.
- COM serializes two 16-bit signals into a four-byte payload.
- PduR maps the configured PDU identifier to a CAN identifier.
- CanIf checks classic-CAN payload length constraints before transmission.
- A deterministic bus queue makes message delivery easy to reproduce in tests.
- Unit-style and integration-style tests cover normal operation and selected invalid inputs.
- The original AUTOSAR learning notes and experiments are retained alongside the maintained simulator.

## What the simulator demonstrates

The simulator focuses on the flow of data through a simplified communication stack. It is intended to help answer questions such as:

- How does an application-level signal move from an SWC toward a communication bus?
- What role does the RTE play between application software and communication services?
- Why does COM package signals into PDUs?
- How does PduR decide which lower communication interface should receive a PDU?
- What responsibility belongs at the CanIf boundary?
- How can an ECU receive a message and expose the decoded value to its application layer?
- How can the individual boundaries be tested independently as well as together?

It does not attempt to reproduce every AUTOSAR service, configuration artefact, or runtime behaviour. The emphasis is on a readable implementation of a small, connected subset of the concepts.

## End-to-end communication flow

The current demonstration models two ECU endpoints and a simulated communication bus:

```text
       ECU A                                                   ECU B
┌─────────────────────┐                              ┌─────────────────────┐
│ Application SWC     │                              │ Application SWC     │
│ produces vehicle    │                              │ consumes vehicle    │
│ status              │                              │ status              │
└──────────┬──────────┘                              └──────────▲──────────┘
           │                                                    │
┌──────────▼──────────┐                              ┌──────────┴──────────┐
│ RTE                 │                              │ RTE                 │
│ ECU-local signal    │                              │ ECU-local signal    │
│ sample storage      │                              │ sample storage      │
└──────────┬──────────┘                              └──────────▲──────────┘
           │                                                    │
┌──────────▼──────────┐                              ┌──────────┴──────────┐
│ COM                 │                              │ COM                 │
│ signal serialization│                             │ signal decoding     │
└──────────┬──────────┘                              └──────────▲──────────┘
           │                                                    │
┌──────────▼──────────┐                              ┌──────────┴──────────┐
│ PduR                │                              │ PduR                │
│ PDU routing         │                              │ PDU routing         │
└──────────┬──────────┘                              └──────────▲──────────┘
           │                                                    │
┌──────────▼──────────┐                              ┌──────────┴──────────┐
│ CanIf               │                              │ CanIf               │
│ CAN interface       │                              │ CAN interface       │
│ boundary            │                              │ boundary            │
└──────────┬──────────┘                              └──────────▲──────────┘
           │                                                    │
           └───────────────┐                    ┌───────────────┘
                           ▼                    ▼
                    ┌──────────────────────────────┐
                    │ Simulated CAN bus            │
                    │ deterministic FIFO queue     │
                    └──────────────────────────────┘
```

### Transmission sequence

1. The ECU A application model writes a vehicle-status sample through its RTE.
2. COM serializes the signal values into a PDU payload.
3. PduR resolves the PDU identifier to the configured CAN identifier.
4. CanIf validates the payload length against the classic-CAN limit.
5. The simulated bus queues the frame.
6. ECU B's CanIf receives the queued frame.
7. PduR maps the CAN identifier back to the corresponding PDU.
8. COM validates and decodes the payload.
9. ECU B's RTE stores the received signal sample for its application model to read.

The two logical ECUs run in the same process for this demonstration. This is intentional: it allows the communication path to be tested deterministically without implying that process-local memory is a transport between independent ECU processes.

## Current vehicle-status message

The current COM example uses one fixed-format vehicle-status PDU containing two unsigned 16-bit values.

| Payload byte | Field | Encoding |
|---|---|---|
| 0 | Vehicle speed, high byte | Unsigned 16-bit, big-endian |
| 1 | Vehicle speed, low byte | Unsigned 16-bit, big-endian |
| 2 | Engine speed, high byte | Unsigned 16-bit, big-endian |
| 3 | Engine speed, low byte | Unsigned 16-bit, big-endian |

**Payload length:** 4 bytes  
**PDU identifier:** `0x0001`  
**Mapped CAN identifier:** `0x120`

For example, the demonstration sends a vehicle speed of `85` and an engine speed of `2400`. These are illustrative values used to exercise serialization and end-to-end delivery; they are not measurements from a vehicle.

The current implementation validates the expected PDU identifier and exact payload length before decoding. The layout is deliberately fixed at this stage. Configuration-driven signal descriptors and more flexible packing are future work.

## Module responsibilities

The maintained implementation is organised under `include/autosar101/` and `src/`.

| Module | Responsibility in this simulator |
|---|---|
| **RTE** | Holds ECU-local, typed signal samples and provides the application-facing read/write boundary. |
| **COM** | Packs and unpacks the vehicle-status signals into/from the four-byte PDU. |
| **PduR** | Maps the configured PDU identifier to the CAN identifier for transmission and performs the reverse mapping on reception. |
| **CanIf** | Represents the hardware-independent CAN interface boundary and validates classic-CAN payload size. |
| **CanBus** | Provides deterministic in-process FIFO delivery between the logical ECU endpoints. |
| **Types** | Defines shared signal, PDU, and frame data structures used by the modules. |

These modules are intentionally small so their responsibilities and interactions can be followed without a large framework or generated configuration.

## Build, test, and run

### Requirements

- CMake 3.16 or newer
- A C++17-compatible compiler:
  - GCC
  - Clang
  - Microsoft Visual C++ (MSVC)
- Git (to clone the repository)

### Clone the repository

```sh
git clone https://github.com/PaweesRaag/AUTOSAR101.git
cd AUTOSAR101
```

The integrated simulator is developed on the feature branch associated with the current pull request. If you are checking out the implementation before it is merged into `main`, use:

```sh
git checkout feature/cohesive-classic-communication-simulator
```

### Configure

For a release build:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```

For a debug build:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
```

### Compile

```sh
cmake --build build --parallel
```

### Run the tests

```sh
ctest --test-dir build --output-on-failure
```

### Run the demonstration

On Linux and macOS:

```sh
./build/autosar101_demo
```

On Windows, the executable is typically:

```powershell
.\build\autosar101_demo.exe
```

With a multi-configuration generator such as Visual Studio, the executable may instead be under a configuration directory, for example `build\Debug\autosar101_demo.exe` or `build\Release\autosar101_demo.exe`.

## Expected demonstration

The demo prints the transmitted and received vehicle-status values, showing that the sample passes through the simulator's communication path. The exact formatting belongs to the current demo implementation; the important expected result is that ECU B receives the same speed and engine-speed values that ECU A sent.

A successful test run verifies the behaviours covered by the automated test suite. It does not prove timing determinism on a real target, conformance to AUTOSAR specifications, or correctness under all possible ECU and bus conditions.

## Test coverage

The test executable exercises the current model at both module and end-to-end level.

| Test area | Behaviour checked |
|---|---|
| COM serialization | Two 16-bit signal values survive pack/unpack round trips. |
| COM boundary values | Zero, maximum 16-bit values, and representative values are handled. |
| COM validation | Unknown PDU identifiers and incorrect payload lengths are rejected. |
| PduR routing | The configured PDU-to-CAN mapping is applied. |
| PduR validation | Unknown CAN identifiers and invalid payload sizes are rejected. |
| CanIf validation | Payloads exceeding the classic-CAN data length limit are rejected. |
| Bus queue | Frames are delivered in FIFO order and empty-queue behaviour is handled. |
| End-to-end transfer | ECU B receives the expected vehicle-status sample after ECU A transmits it. |

Run the test suite locally with CTest using the command above. The GitHub Actions workflow also configures the project, builds it, runs CTest, and executes the demo on pushes and pull requests.

## Repository structure

```text
AUTOSAR101/
├── .github/
│   └── workflows/
│       └── cpp.yml                 # Build, test, and demo CI workflow
├── AUTOSAR/                        # Original learning notes and experiments
│   ├── ECU_A/                       # Early ECU A / SWC / RTE experiments
│   ├── ECU_B/                       # Early ECU B / SWC / RTE experiments
│   ├── COM/                         # Earlier COM and routing demonstrations
│   ├── shared/                      # Shared code from early experiments
│   ├── README.md                    # Original learning notes
│   └── PartI.md                     # Learning curriculum and notes
├── docs/
│   ├── ARCHITECTURE.md              # Current simulator architecture
│   └── ROADMAP.md                   # Planned extensions
├── include/
│   └── autosar101/
│       ├── can_bus.hpp
│       ├── can_if.hpp
│       ├── com.hpp
│       ├── pdur.hpp
│       ├── rte.hpp
│       └── types.hpp
├── src/
│   ├── can_bus.cpp
│   ├── can_if.cpp
│   ├── com.cpp
│   ├── main.cpp
│   └── pdur.cpp
├── tests/
│   └── test_main.cpp
├── .gitignore
├── CMakeLists.txt
└── README.md
```

The exact contents of the historical `AUTOSAR/` directory may evolve as the learning archive grows. The maintained integrated CMake target is built from the `include/`, `src/`, and `tests/` directories.

## Original learning material

The original experiments are kept because they show the progression from individual concepts toward an integrated communication path. They include examples and notes related to:

- Software Components and application-level code
- Ports and sender-receiver communication concepts
- Early RTE experiments
- COM and signal/PDU handling
- PduR and CanIf-oriented demonstrations

Some early experiments are standalone examples and are not compiled into the maintained CMake simulator. They should be read as learning artefacts, not as a second implementation of the current integrated stack.

Useful starting points:

- [Original AUTOSAR learning notes](AUTOSAR/README.md)
- [Part I — learning curriculum and notes](AUTOSAR/PartI.md)
- [Current architecture](docs/ARCHITECTURE.md)
- [Development roadmap](docs/ROADMAP.md)

## Design decisions and current limitations

The simulator prioritises clarity and testability over protocol completeness.

### Deliberate simplifications

- **In-process endpoints:** Both ECU endpoints run within one process. The bus queue is a simulation mechanism, not inter-process or physical communication.
- **Fixed COM layout:** The vehicle-status PDU has two fixed 16-bit big-endian signals. There is no configuration-driven signal database, arbitrary bit position, scaling, or signal invalidation handling yet.
- **Single route:** The model currently demonstrates one PDU and one CAN identifier rather than a general routing configuration.
- **Simplified CAN interface:** CanIf checks payload length but does not implement a hardware controller, driver, interrupt path, or complete CAN protocol behaviour.
- **Deterministic queue:** The simulated bus provides FIFO delivery. It does not model arbitration, bus load, bit timing, retransmission, error confinement, or physical-layer faults.
- **Educational RTE:** The RTE is a small typed sample store, not generated AUTOSAR RTE code and not a full implementation of queued/unqueued communication semantics.

### Not implemented

The current simulator does not include:

- AUTOSAR XML (ARXML) configuration or code generation
- A full AUTOSAR Classic Platform BSW stack
- MCAL or a target-specific CAN controller driver
- Physical CAN transceiver or ECU hardware integration
- CAN arbitration, bit timing, CRC, ACK, error frames, or bus-off recovery
- Operating-system scheduling, task activation, interrupts, or timing analysis
- UDS, DCM, DEM, NvM, or diagnostic event handling
- SecOC, cryptographic freshness management, or key provisioning
- Functional-safety analysis or cybersecurity certification

These are meaningful areas for future exploration, but they should not be inferred from the modules currently present.

## Roadmap

The next development milestones are tracked in [docs/ROADMAP.md](docs/ROADMAP.md). Broadly, the planned direction is:

1. **Configuration-driven COM:** Define signal layouts through descriptors rather than hardcoded packing logic.
2. **Multiple PDU routes:** Support more than one PDU and route with explicit configuration and validation.
3. **Richer CAN simulation:** Introduce selected frame semantics and bus behaviour while keeping the model deterministic and testable.
4. **RTE communication semantics:** Explore queued and unqueued data access and clearer sender-receiver behaviour.
5. **Diagnostics learning model:** Add a scoped educational model for diagnostic concepts such as UDS, DCM, and DEM.
6. **Security concepts:** Explore SecOC and freshness concepts using a vetted cryptographic library rather than custom cryptography.
7. **Hardware-facing extension:** Consider a target-specific or SocketCAN-backed transport only when the platform and test environment are explicitly defined.

The roadmap is aspirational. A listed item should not be considered implemented until code, tests, and documentation demonstrate it.

## Learning objectives

This repository is useful as a practical companion while studying embedded software architecture and automotive communication concepts. Working through it can help develop familiarity with:

- Layered embedded-software architecture and separation of concerns
- The relationship between SWCs, RTE concepts, and BSW communication modules
- Signal serialization and deserialization
- PDU identifiers and routing boundaries
- CAN payload constraints
- C++ interfaces, data structures, and defensive validation
- Unit testing and end-to-end integration testing
- CMake-based C++ project organisation
- Continuous integration with GitHub Actions
- The difference between a conceptual simulator and a hardware-validated implementation

## Contributing

Issues, corrections, and focused educational extensions are welcome. When proposing a change:

1. Keep module responsibilities explicit.
2. Add tests for both valid inputs and relevant invalid or boundary cases.
3. Update the architecture and roadmap when behaviour or scope changes.
4. Clearly distinguish simulated behaviour from hardware or standards-based implementation.
5. Avoid describing an educational approximation as AUTOSAR-compliant or production-ready.

## Disclaimer

AUTOSAR101 is an independent educational project. AUTOSAR is a registered trademark of its respective owners. This repository is not affiliated with, endorsed by, or certified by the AUTOSAR organisation.

All protocol and architecture references are used for learning purposes. Automated tests demonstrate only the behaviour implemented and tested in this repository; they are not evidence of standards conformance, automotive functional safety, cybersecurity certification, production readiness, or physical ECU/CAN validation.
