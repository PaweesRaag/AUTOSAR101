# Implementation Roadmap

## Phase 1 — Foundation

- [x] Separate learning notes from the root README
- [x] Define the simulated multi-ECU architecture
- [x] Add repository hygiene rules
- [ ] Normalize naming and headers
- [ ] Add reproducible build instructions

## Phase 2 — RTE and SWCs

- [ ] Model sender/receiver interfaces explicitly
- [ ] Define P-Port and R-Port abstractions
- [ ] Define runnable entry points
- [ ] Remove direct cross-layer data access
- [ ] Add focused unit tests

## Phase 3 — Communication Stack

- [ ] COM signal packing/unpacking
- [ ] PduR routing API
- [ ] CanIf abstraction
- [ ] CAN frame model
- [ ] Deterministic CAN bus simulator
- [ ] End-to-end ECU A → ECU B demo

## Phase 4 — Diagnostics

- [ ] UDS request/response model
- [ ] DCM service dispatcher
- [ ] DEM event/DTC model
- [ ] Security Access demonstration
- [ ] Diagnostic test cases

## Phase 5 — Automotive Security

- [ ] SecOC message authentication model
- [ ] Freshness counter
- [ ] AES-CMAC integration/adapter
- [ ] Tamper detection demo
- [ ] Replay detection demo
- [ ] Security-focused unit tests

## Phase 6 — Engineering Quality

- [ ] CMake build
- [ ] GitHub Actions CI
- [ ] Compiler warnings as errors
- [ ] Formatting/linting
- [ ] Coverage reporting
- [ ] Clean release/demo instructions

## Optional Extensions

- [ ] NvM / memory-stack simulation
- [ ] Automotive Ethernet abstraction
- [ ] SOME/IP / service discovery concepts
- [ ] Binary reverse-engineering exercises
