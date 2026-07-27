# Introduction to AUTOSAR

## What is AUTOSAR?

**AUTOSAR (AUTomotive Open System ARchitecture)** is a global standard for automotive software architecture. It was created by major automotive manufacturers, suppliers, and technology companies to provide a common framework for developing vehicle software.

In simple terms, AUTOSAR is a set of rules and standardized software layers that allow automotive software to be developed in a modular, reusable, and scalable way.

***

## Why Was AUTOSAR Created?

Before AUTOSAR, every vehicle manufacturer used its own software architecture. This created several problems:

* Software had to be rewritten for different vehicles and ECUs.
* Integration between suppliers was difficult.
* Development and maintenance costs were high.
* Reusing software across projects was challenging.

AUTOSAR solves these issues by defining a common architecture that can be used across the automotive industry.

Benefits include:

* ✅ Software Reusability
* ✅ Standardization
* ✅ Easier Integration
* ✅ Reduced Development Time
* ✅ Supplier Independence
* ✅ Improved Maintainability

***

## The AUTOSAR Layered Architecture

AUTOSAR separates software into different layers, each with a specific responsibility.

```text
+----------------------+
|  Application Layer   |
+----------------------+
           |
+----------------------+
|         RTE          |
| Runtime Environment  |
+----------------------+
           |
+----------------------+
|   Basic Software     |
|       (BSW)          |
+----------------------+
           |
+----------------------+
|         MCAL         |
+----------------------+
           |
+----------------------+
|      Hardware        |
+----------------------+
```

### 1. Application Layer

Contains the actual vehicle functionality.

Examples:

* Cruise Control
* ABS Logic
* Battery Monitoring
* Door Lock Control
* Airbag Logic

These functionalities are implemented as **Software Components (SWCs)**.

***

### 2. RTE (Runtime Environment)

The RTE acts as a communication layer between Software Components and the underlying AUTOSAR services.

Think of it as a messenger or middleware that enables components to exchange data without directly depending on each other.

```text
SWC A
  |
 RTE
  |
SWC B
```

***

### 3. BSW (Basic Software)

Provides common services required by the application.

Examples:

* Communication Services
* Diagnostic Services
* Memory Services
* Operating System Services
* Security Services

The BSW hides hardware complexity from the application.

***

### 4. MCAL (Microcontroller Abstraction Layer)

The MCAL contains low-level drivers that interact directly with the microcontroller hardware.

Examples:

* CAN Driver
* SPI Driver
* ADC Driver
* PWM Driver
* DIO Driver

This layer isolates higher software layers from hardware-specific details.

***

## ECU and SWC

### ECU (Electronic Control Unit)

An ECU is a physical embedded computer inside a vehicle.

Examples:

* Engine ECU
* ABS ECU
* Airbag ECU

### SWC (Software Component)

An SWC is a software module that performs a particular function.

Examples:

* Cruise Control SWC
* Vehicle Speed SWC
* Door Lock SWC

A single ECU can host multiple SWCs.

```text
Engine ECU
├── Vehicle Speed SWC
├── Cruise Control SWC
└── Diagnostics SWC
```

***

## Communication in AUTOSAR

AUTOSAR communication can be divided into two categories.

### 1. Intra-ECU Communication

Communication between SWCs inside the same ECU.

```text
SWC
 ↓
RTE
 ↓
SWC
```

Handled by:

```text
RTE
```

***

### 2. Inter-ECU Communication

Communication between different ECUs.

```text
ECU A
  |
CAN Bus
  |
ECU B
```

Handled by the **COM Stack**.

```text
COM
 ↓
PduR
 ↓
CanIf
 ↓
CanDrv
```

***

## Diagnostics in AUTOSAR

AUTOSAR provides a standardized diagnostic framework.

Main modules:

### DCM (Diagnostic Communication Manager)

Handles communication with diagnostic testers.

### DEM (Diagnostic Event Manager)

Stores Diagnostic Trouble Codes (DTCs) and fault information.

### FiM (Function Inhibition Manager)

Disables certain functions when faults are detected.

### DET (Development Error Tracer)

Used for development-time debugging and error reporting.

***

## Security in AUTOSAR

Modern vehicles require secure communication between ECUs.

### SecOC (Secure Onboard Communication)

Provides:

* Authentication
* Integrity
* Replay Protection

SecOC protects messages using:

```text
Message
+
Freshness Value
+
MAC (Message Authentication Code)
```

***

## Crypto Stack

AUTOSAR uses a dedicated Crypto Stack to perform cryptographic operations.

```text
SecOC
 ↓
CSM
 ↓
CryIf
 ↓
Crypto Driver
 ↓
HSM
```

Where:

* **CSM** → Crypto Service Manager
* **CryIf** → Crypto Interface
* **Crypto Driver** → Executes cryptographic algorithms
* **HSM** → Hardware Security Module

***

## Memory Stack

AUTOSAR provides a Memory Stack for storing data permanently.

```text
NvM
 ↓
MemIf
 ↓
Fee / Ea
 ↓
Flash / EEPROM
```

Used to store:

* DTCs
* Odometer values
* Calibration data
* Configuration parameters
* Security counters

This ensures that important data survives ignition OFF and power cycles.

***

## Big Picture

```text
Application SWCs
      |
      v
     RTE
      |
      v
+----------------------+
|    Basic Software    |
|                      |
| COM Stack            |
| Diagnostic Stack     |
| Crypto Stack         |
| Memory Stack         |
+----------------------+
      |
      v
     MCAL
      |
      v
   Hardware
```

***


