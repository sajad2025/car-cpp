# Car Simulation Project

A vehicle trajectory simulation using a kinematic model with closed-loop control.

## Prerequisites

- C++ compiler (g++ or clang++)
- Make
- Python 3.6+

## Quick Start

Run the all-in-one build script:

```bash
chmod +x build.sh
./build.sh
```

This will:
- Build the C++ project
- Run the simulation
- Generate trajectory data in `docs/trajectory.txt`
- Create plots in `docs/trajectory.png`

## Project Structure

- `src/`: C++ source code
- `docs/`: Output files
- `build/`: Compiled binaries
- `plots.py`: Visualization script
- `build.sh`: Build and run script
- `setup.sh`: Python environment setup

## Manual Usage

### Build and Run C++

```bash
make
./build/car_sim
```

### Setup Python Environment

```bash
source setup.sh
```

### Generate Plots

```bash
python plots.py [--file PATH] [--output DIR]
```

## Development Workflow

1. Edit source files in `src/`
2. Run `./build.sh` to rebuild, run, and visualize
3. Or run individual steps manually as needed 