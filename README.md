# Car Simulation Project

This project simulates a vehicle trajectory using a kinematic model with closed-loop control. The simulation generates trajectory data that can be visualized using the included plotting tools.

## Project Structure

- `src/`: C++ source code for the vehicle simulation
- `docs/`: Output files and documentation
- `build/`: Compiled binaries
- `plots.py`: Python script for visualizing trajectory data
- `setup.sh`: Script to set up and activate the Python virtual environment

## Building and Running the C++ Project

### Prerequisites

- C++ compiler (g++ or clang++)
- Make

### Build Instructions

To build the project, run:

```bash
make
```

This will compile the source code and create the executable in the `build/` directory.

### Running the Simulation

To run the simulation, execute:

```bash
./build/car_sim
```

This will:
1. Run the vehicle simulation with closed-loop control
2. Generate trajectory data
3. Save the trajectory data to `docs/trajectory_with_errors.txt`

## Visualizing the Results

### Prerequisites

- Python 3.6 or higher

### Setting Up and Running the Plotting Tool

#### Option 1: Setup and Activate in One Step (Recommended)

To set up and activate the virtual environment in one step, run:

```bash
chmod +x setup.sh
source setup.sh
```

This will:
1. Create a virtual environment (if it doesn't exist)
2. Install required packages
3. Activate the environment in your current shell
4. You can then run `python plots.py` directly

#### Option 2: Manual Setup and Activation

If you prefer to set up and activate separately:

1. Set up the environment:
```bash
./setup.sh
```

2. Activate the environment:
```bash
source venv/bin/activate
```

3. Run the plotting script:
```bash
python plots.py
```

When finished, deactivate the environment:

```bash
deactivate
```

### Plotting the Trajectory

The plotting script will:
1. Read the trajectory data from `docs/trajectory_with_errors.txt`
2. Generate plots showing:
   - Vehicle trajectory (x, y)
   - Velocity and acceleration profiles
   - Steering angle
   - Tracking errors (lateral, longitudinal, heading)
3. Save the plots to `docs/trajectory_plots.png`
4. Display the plots on screen

### Custom Plotting Options

You can specify a different trajectory file or output directory:

```bash
python plots.py --file path/to/trajectory.txt --output path/to/output/dir
```

## Development

To make changes to the C++ code:
1. Edit the source files in the `src/` directory
2. Run `make` to rebuild
3. Run `./build/car_sim` to generate new trajectory data
4. Activate the environment with `source setup.sh` if not already active
5. Run `python plots.py` to visualize the updated results
6. Deactivate the environment when finished with `deactivate` 