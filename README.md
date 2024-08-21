# SynradBenchmark

## Overview

SynradBenchmark is a benchmarking suite designed to evaluate the performance and accuracy of various Synrad-based codes, including SynradG4, Synrad+ (version 1.4.34), Synrad3D, and Geant4 (version 11.2.0). The primary focus of this repository is to benchmark photon reflection models in vacuum beam pipes, taking into account surface roughness and photon interactions.

## Goals

This repository aims to provide:

- A comparative analysis of photon reflection models.
- Benchmarking scripts for testing SynradG4, Synrad+, Synrad3D, and Geant4.
- Documentation of performance metrics for surface roughness in a vacuum beam pipe.
- Easy-to-reproduce simulation environments for developers and researchers working in the field of high-energy physics and vacuum technology.

## Prerequisites

Before using SynradBenchmark, ensure that you have the following dependencies installed:

- SynradG4
- [Synrad+](https://gitlab.cern.ch/molflow_synrad/synrad)
- [Synrad3D](https://github.com/bmad-sim/bmad-ecosystem.git)
- [Geant4 11.2.0](https://geant4.web.cern.ch/download/11.2.0.html)
 
Additional packages:

- CMake
- GNU Make
- Python 3.x (for data processing and plotting)
- gnuplot (for visualization)
- ROOT CERN (for data storage and analysis)
- Bmad (for the Synrad3D simulation)

## Installation

1. Clone the repository:
```bash
git clone https://github.com/nat93/SynradBenchmark.git
cd SynradBenchmark
```
2. Set up the required dependencies and environment for each tool.

## Usage

Please navigate to `README` files in each framework directory.

## Contributing

Contributions to SynradBenchmark are welcome! Feel free to open issues, submit pull requests, or suggest improvements.

### Author
Andrii Natochii
E-mail: [natochii@bnl.gov](mailto:natochii@bnl.gov)

