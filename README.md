# AUTOSAR101

An educational C++ project exploring AUTOSAR Classic concepts through small,
executable models. The repository preserves the original learning notes and
experiments while adding a structured, testable communication-stack simulator.

> **Scope disclaimer:** This is an AUTOSAR-inspired educational simulation,
> not an AUTOSAR-compliant implementation, generated RTE/BSW, production ECU
> software, or physical CAN implementation.

## Current implementation

The new C++ simulator demonstrates a complete in-process signal path between
two independently modelled ECUs:

```text
ECU A SWC -> RTE -> COM -> PduR -> CanIf
                                      |
                                Simulated CAN bus
                                      |
ECU B SWC <- RTE <- COM <- PduR <- CanIf
```

- **RTE:** ECU-local typed sender-receiver sample storage.
- **COM:** packs/unpacks a 16-bit vehicle-speed signal in big-endian order.
- **PduR:** maps the configured PDU identifier to/from CAN ID `0x120`.
- **CanIf:** hardware-independent boundary with classic-CAN DLC validation.
- **CanBus:** deterministic FIFO transport queue for the two ECU endpoints.
- **Tests:** signal round trips, malformed PDUs, routing, FIFO behaviour,
  invalid DLC and an end-to-end ECU A → ECU B integration test.

The current model intentionally contains one signal, one PDU and one CAN ID.
See [Architecture](docs/ARCHITECTURE.md) for module boundaries and limitations.

## Build, test and run

Requirements: CMake 3.16+ and a C++17 compiler.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
ctest --test-dir build --output-on-failure
./build/autosar101_demo
```

On Windows, run the generated executable at `build\\autosar101_demo.exe`
(or the corresponding configuration subdirectory when using a multi-config
generator).

GitHub Actions builds the project and runs CTest on pushes and pull requests.

## Repository layout

```text
include/autosar101/   Public module interfaces and shared types
src/                 COM, PduR, CanIf, bus and demonstration
tests/               Unit and end-to-end tests
docs/                Architecture and development roadmap
AUTOSAR/              Original learning experiments and notes
```

The original material under `AUTOSAR/` is retained as a record of the learning
progression: SWCs, ports, RTE experiments, COM and PduR/CanIf demonstrations.
Some early experiments are intentionally not part of the new CMake target;
they are historical learning examples, not the maintained integrated build.

## Roadmap

See [docs/ROADMAP.md](docs/ROADMAP.md). Planned extensions include
configuration-driven signal packing, multiple PDU routes, richer CAN frame
semantics, queued/unqueued RTE communication, a UDS/DCM/DEM teaching model and
a SecOC model backed by a vetted cryptographic library.

## Learning notes

- [AUTOSAR introduction](AUTOSAR/README.md)
- [Part I — learning curriculum and notes](AUTOSAR/PartI.md)
- [Implementation architecture](docs/ARCHITECTURE.md)
- [Development roadmap](docs/ROADMAP.md)

## Contributions and claims

The project is intended for learning, experimentation and interview discussion.
Passing automated tests verifies this simulator's stated behaviour only. It
does not establish AUTOSAR conformance, timing behaviour, functional safety,
cybersecurity certification, or physical CAN hardware validation.
