
# Activation_PuBe

## Overview

This repository contains a **Geant4-based simulation framework** for studying neutron activation using a **PuBe (Plutonium–Beryllium) source**. The primary goal is to model neutron interactions, material activation (e.g., tin isotopes), and detector response in a controlled geometry.

This project is part of ongoing detector and activation studies relevant to low-background experiments and calibration workflows.

---

## Features

- Geant4-based detector and geometry definition  
- PuBe neutron source modeling  
- Primary generator customization  
- Physics list integration for neutron interactions  
- Output handling via Geant4 analysis tools  

---

## Repository Structure


Activation_PuBe/
├── src/ # Core simulation source files
│ ├── DetectorConstruction.cc
│ ├── PrimaryGeneratorAction.cc
│ ├── RunAction.cc
│ ├── EventAction.cc
│ └── ...
├── include/ # Header files
├── macros/ # Geant4 macro files for running simulations
├── build/ # Build directory (generated)
├── CMakeLists.txt # Build configuration
└── README.md


---

## Requirements

- Geant4 (recommended ≥ 10.7 or 11.x)
- CMake (≥ 3.10)
- C++17 compatible compiler
- ROOT (optional, for advanced analysis)
- Python (optional, for post-processing)

---

## Installation

### 1. Clone the repository

```bash
git clone https://github.com/pratyush06853/Activation_PuBe.git
cd Activation_PuBe
2. Setup Geant4 environment

Make sure Geant4 is sourced:

source /path/to/geant4-install/bin/geant4.sh
3. Build
mkdir Activation_PuBe_build
cd Activation_PuBe_build
cmake ..
make -j4
Running the Simulation

Run using a macro: all the relevant macros are in DTMacros folder

./IronFilter -m  ../Activation_PuBe/DTMacros/run.mac

Or interactive mode:

./IronFilter
Physics and Simulation Details
Source
PuBe neutron source
Energy spectrum modeled according to standard PuBe distributions
Geometry
Iron filter + backing detector configuration
Modular geometry allowing easy modification
Physics
Standard Geant4 physics lists for neutron interactions
Includes capture, scattering, and activation processes
Output
Event-level data (energy deposition, interaction positions)
Activation products (depending on physics list)
Optional histogram output via Geant4 analysis manager
Known Issues / Notes
Some Geant4 API differences may require minor updates depending on version:
G4VisAttributes::Invisible may not be available
G4TouchableHandle vs G4TouchableHistoryHandle
Ensure proper linking of Geant4 analysis libraries
Large simulations may require batch execution (not recommended in interactive mode)
