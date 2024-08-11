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
This project simulates the propagation of synchrotron radiation (SR) emited by 18-GeV electons through a vacuum beam pipe using the Geant4 toolkit. The primary goal is to model the interaction of SR photons with the beam pipe's material and calculate the reflection probability with different scattering models.

## Features
- **Geant4-based simulation**: Utilizes the Geant4 libraries for accurate photon propagation through the geometry.
- **Custom geometry**: Define and simulate the vacuum beam pipe geometry.
- **Tracking**: Track synchrotron radiation.
- **Material interaction**: Simulate SR interactions with various materials through absorbtion on reflection on the vacuum-material border.
- **Modular design**: Easily modify or extend the simulation components.

## Prerequisites
- **Operating System**: Linux, macOS, or Windows
- **C++ Compiler**: GCC, Clang, or MSVC with C++17 support
- **Geant4 Toolkit**: Version 11.0 or later
- **CMake**: Version 3.12 or later
- **ROOT**: For the output data storage and analysis 
- **Qt5** (Option): For visualization

## Installation

### 1. Unzip the code arciver 
```bash
tar -xvf SynradG4.tar.gz
cd SynradG4/
```

### 2. Install Dependencies
Ensure that Geant4 and other dependencies are installed on your system.

### 3. Build the Project
```bash
cd sim/
mkdir build
cd build/
cmake ..
make
```

## Usage

### Running the Simulation
After building the project, you can run the simulation using:

- Visualization:
```bash
./exe vis.mac ../geometry/setup.xml $RANDOM
```

- High statistics simulation
```bash
./exe run.mac ../geometry/setup.xml $RANDOM
```

### Configuring Simulation Parameters
Modify the configuration file `setup.xml` to adjust parameters such as:

- SR photon reflection model
- Data priting
- Surface roughness
- Surface autocorrelation length
- Surface roughness ration

```sql
<xml>
	<!-- synrad model -->
	<srmodel>
		<sec desc="SR photon reflection process: 0 - Geant4 (Xray,Névot-Croce); 1 - Synrad+ (Gamma,Debye-Waller); 2 - Synrad+ (Gamma,perturb norm - old model); 3 - Synrad+ (Gamma,Debye-Waller,perturb refl - new model)" name="type">3</sec>
		<sec desc="Print SR photon reflection data: 1 - true; 0 - false" name="print">1</sec>
		<sec desc="Surface roughness" name="roughness" unit="m">50e-9</sec>
		<sec desc="Surface autocorrelation length" name="corrlength" unit="m">10000e-9</sec>
		<sec desc="Surface roughness ratio" name="sigma" unit="">5e-3</sec>
	</srmodel>
</xml>
```

In `run.mac` and `vis.mac`, define the number of initially generated electrons, visualization parameters, and the output file name.

`$RANDOM` provides a seed for the random number generator used in the code

### Output
The simulation will generate output files that include:

- Generated electron beam parameters
- SR photon production vertecies
- Photon absorbtion coordinates, energy, and time
- XML file and random seed

## Directory Structure

```makefile
SynradG4/sim/
│
├── src/                  # Source files for the simulation
├── include/              # Header files
├── build/                # Build directory
├── output/               # Output data from simulations
├── CMakeLists.txt        # CMake build script
├── geometry/setup.xml    # Configuration file with SR reflection model
├── vis.mac               # Visualization file 
├── run.mac               # High statistics simulation file 
├── main.cc               # Main source file 
├── materials             # Reflection probability coeficient files 
├── runAll.bash           # BASH script to automatically create a `run.mac` file  
└── runScreens_scan.bash  # BASH script to submit multiple simulations on different CPUs 

SynradG4/ana/
│
├── src/                  # Source files for the simulation
├── include/              # Header files
├── build/                # Build directory
├── output/               # Output data from simulations
├── CMakeLists.txt        # CMake build script
├── geometry/setup.xml    # Configuration file with SR reflection model
├── vis.mac               # Visualization file 
├── run.mac               # High statistics simulation file 
├── main.cc               # Main source file 
├── materials             # Reflection probability coeficient files 
├── runAll.bash           # BASH script to automatically create a `run.mac` file  
├── runScreens_scan.bash  # BASH script to submit multiple simulations on different CPUs 

└── README.md             # Project documentation
```

## Contributing

Contributions are welcome!

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contact

For any questions or further information, please contact:

- Your Name - <natochii@bnl.gov>
- GitHub: [nat93](https://github.com/nat93)
