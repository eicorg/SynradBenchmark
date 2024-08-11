# Synchrotron Radiation Simulation with Geant4 (**SynradG4**)

## Table of Contents
- [Project Description](#project-description)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Simulation Parameters](#simulation-parameters)
- [Directory Structure](#directory-structure)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Project Description
This project simulates the propagation of synchrotron radiation through a vacuum beam pipe using the Geant4 toolkit. The primary goal is to model the interaction of high-energy photons with the beam pipe's material and calculate the resulting energy deposition and transmission.

## Features
- **Geant4-based simulation**: Utilizes the Geant4 libraries for accurate physics modeling.
- **Custom geometry**: Define and simulate the vacuum beam pipe geometry.
- **Energy deposition tracking**: Track and record energy deposited by synchrotron radiation.
- **Material interaction**: Simulate interactions with various materials.
- **Modular design**: Easily modify or extend the simulation components.

## Prerequisites
- **Operating System**: Linux, macOS, or Windows
- **C++ Compiler**: GCC, Clang, or MSVC with C++17 support
- **Geant4 Toolkit**: Version 10.7 or later
- **CMake**: Version 3.12 or later
- **GSL (GNU Scientific Library)**: For statistical analysis
- **ROOT** (Optional): For advanced data analysis and visualization

## Installation

### 1. Clone the Repository
```bash
git clone https://github.com/yourusername/synchrotron-simulation.git
cd synchrotron-simulation
```

### 2. Install Dependencies
Ensure that Geant4 and other dependencies are installed on your system.

### 3. Build the Project
```bash
mkdir build
cd build
cmake ..
make
```

## Usage

### Running the Simulation
After building the project, you can run the simulation using:

```bash
./synchrotron_simulation
```

### Configuring Simulation Parameters
Modify the configuration file `config.in` to adjust parameters such as:

- Photon energy range
- Beam pipe dimensions
- Material properties
- Number of simulation events

### Output
The simulation will generate output files that include:

- Energy deposition data
- Photon transmission rates
- Geant4 logs

## Simulation Parameters

- **PhotonEnergyRange**: Specifies the range of photon energies (e.g., 1 keV to 10 MeV).
- **BeamPipeMaterial**: Define the material of the beam pipe (e.g., Aluminum, Copper).
- **Geometry**: Configure the dimensions and shape of the vacuum beam pipe.
- **NumberOfEvents**: Set the number of photons to simulate.

## Directory Structure

```makefile
synchrotron-simulation/
│
├── src/                  # Source files for the simulation
├── include/              # Header files
├── data/                 # Data files and configuration
├── build/                # Build directory
├── results/              # Output data from simulations
├── CMakeLists.txt        # CMake build script
├── config.in             # Configuration file
└── README.md             # Project documentation
```

## Contributing

Contributions are welcome! Please fork this repository, create a new branch, and submit a pull request.

## Reporting Issues
If you encounter any issues, please report them using the GitHub Issues tab.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contact

For any questions or further information, please contact:

- Your Name - <natochii@bnl.gov>
- GitHub: [nat93](https://github.com/nat93)
