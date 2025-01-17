# Synchrotron Radiation Simulation with Geant4 (**SynradG4**)

## Table of Contents
- [Project Description](#project-description)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Simulation Directory Structure](#simulation-directory-structure)
- [Analysis](#analysis)
- [Analysis Directory Structure](#analysis-directory-structure)
- [Contributing](#contributing)
- [Contact](#contact)

## Project Description
This framework simulates the propagation of synchrotron radiation (SR) emitted by 18-GeV electrons through a vacuum beam pipe using the Geant4 toolkit. The primary goal is to model the interaction of SR photons with the beam pipe's material and calculate the reflection probability with different scattering models.

Furthermore, there is a code dedicated to analyzing the output data and building histograms with absorbed SR photons on the vacuum beam pipe walls.

## Features
- **Geant4-based simulation**: Utilizes the Geant4 libraries for accurate photon propagation through the geometry.
- **Custom geometry**: Defines and simulates the vacuum.
- **Tracking**: Tracks SR photons.
- **Material interaction**: Simulates SR interactions with various materials through absorption or reflection on the vacuum-material border.
- **Modular design**: Easily modifies and extends the simulation components.

## Prerequisites
- **Operating System**: Linux or macOS
- **C++ Compiler**: GCC or Clang
- **Geant4 Toolkit**: Version 11.0 or later
- **CMake**: Version 3.5 or later
- **ROOT**: Version 6.24 or later, for the output data storage and analysis 
- **Qt5** (Option): For visualization

## Installation

### 1. Clone 
```bash
git clone git@github.com:eicorg/SynradBenchmark.git
cd SynradBenchmark/SynradG4/
```

### 2. Install Dependencies
Please ensure that Geant4, ROOT, and other dependencies are installed on your system.

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

Or simply use the BASH script in `SynradG4/sim/`:
```bash
./runScreens.bash
```

### Configuring Simulation Parameters
Modify the configuration file `setup.xml` to adjust parameters such as:

- SR photon reflection model
- Data printing
- Surface roughness
- Surface autocorrelation length
- Surface roughness ratio

```sql
<xml>
	<!-- synrad model -->
	<srmodel>
		<sec desc="SR photon reflection process: 
			0 - Geant4 (Xray,Névot-Croce); 
			1 - Synrad+ (Gamma,Debye-Waller); 
			2 - Synrad+ (Gamma,perturb norm - old model); 
			3 - Synrad+ (Gamma,Debye-Waller,perturb refl - new model)" name="type">3</sec>
		<sec desc="Print SR photon reflection data: 
			1 - true; 
			0 - false" name="print">1</sec>
		<sec desc="Surface roughness" 
			name="roughness" unit="m">50e-9</sec>
		<sec desc="Surface autocorrelation length" 
			name="corrlength" unit="m">10000e-9</sec>
		<sec desc="Surface roughness ratio" 
			name="sigma" unit="">5e-3</sec>
	</srmodel>
</xml>
```

In `run.mac` and `vis.mac`, define the number of initially generated electrons, visualization parameters, and the output file name.

`$RANDOM` provides a seed for the random number generator used in the code.

### Geometry modeling

There is a simple 50-m-long vacuum of the beamline pipe. After 5 m of a drift space, there is a 5-m-long uniform dipole field region with 10 mrad of bending radius. A pencil beam of 18 GeV electrons is shot from (0;0;0) towards the positive direction of the Z-axis. SR photons generated in the dipole field through the Geant4 process `G4SynchrotronRadiation` are propagated along the vacuum until absorbed. The simulation assumes that the beam pipe wall outside the vacuum is made of copper with surface parameters described in the XML file. 

![Alt text](pic.png)

### SR reflection model 

There are four options for the SR reflection model to be used in the simulation. Most of them are for testing or benchmarking purposes, while the last in the list `#3` is used as the default one. Here is a brief description of the models:

0. Inherited from the recently developed (Dec. 2023) Geant4 process `G4XrayReflection` with specular reflection only and based on Névot-Croce attenuation factors [[Ref.](https://geant4.web.cern.ch/download/11.2.0.html)].
1. Specular reflection process based on Debye–Waller attenuation factors [[Ref.](https://doi.org/10.1364/OSAC.422924)].
2. Diffuse reflection without attenuation factors, similar to `Synrad+` **old** model [[Ref.](https://molflow.web.cern.ch/node/116)].
3. Diffuse reflection with Névot-Croce attenuation factors, similar to `Synrad+` **new** model [[Ref.](https://molflow.web.cern.ch/node/116)].

### Output
The simulation will generate output files that include:

- Generated electron beam parameters
- SR photon production vertices
- Photon absorption coordinates, energy, and time
- XML file and random seed

## Simulation Directory Structure

```makefile
SynradG4/sim/
│
├── src/                  # Source files for the simulation
├── include/              # Header files
├── CMakeLists.txt        # CMake build script
├── geometry/setup.xml    # Configuration file with SR reflection model
├── vis.mac               # Visualization file 
├── run.mac               # High statistics simulation file 
├── main.cc               # Main source file 
├── materials/            # Reflection probability coefficient files 
├── runAll.bash           # BASH script to automatically create a `run.mac` file  
└── runScreens.bash       # BASH script to submit multiple simulations on different CPUs 
```

## Analysis
To analyze the simulation output, go to `SynradG4/ana/`. The code is developed to read the output file after the SR simulation and build histograms with photon distributions.

### 1. Build
```bash
mkdir buid
cd build/
cmake ../
make
``` 

### 2. Run
```bash
rm -rf mainInDir/sim_output_all.root
hadd -f mainInDir/sim_output_all.root mainInDir/sim_output_*.root
./exe mainInDir sim_output_all.root outputDir ana_output_all.root treeName
```

Or simply use the BASH script in `SynradG4/ana/`:
```bash
./runAna.bash
```

- `mainInDir` is the input directory where SR simulation output files are stored
- `sim_output_all.root` contains data of all merged output files
- `outputDir` output directory for the analysis
- `ana_output_all` output analysis file name
- `treeName` is the name of the ROOT Tree with SR data in `sim_output_all.root`

In the file `SynradG4/ana/src/AnalysisSR.cc`, one can define the region of ineterest for detailed SR distributions:
```bash
if(     40e2 < gammaPosZ_cm->at(i) && gammaPosZ_cm->at(i) < 45e2        )
```
By default, some histograms will be built for absorbed SR photons between 40 m and 45 m.


## Analysis Directory Structure
```makefile
SynradG4/ana/
│
├── src/                  # Source and header files for the analysis
├── CMakeLists.txt        # CMake build script
└── runAna.bash           # BASH script to run the analysis 
```

## Contributing

Contributions are welcome!

## Contact

For any questions or further information, please contact:

- Andrii Natochii - <natochii@bnl.gov>
