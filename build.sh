#!/bin/bash

# Exit on error
set -e

echo "=== Building Car Simulation Project ==="

# Create build directory if it doesn't exist
mkdir -p build

# Build the project using make
echo "Building project..."
make

# Ensure docs directory exists for output
mkdir -p docs

# Run the simulation
echo "Running simulation..."
./build/car_sim

# Check if virtual environment exists, if not create it
if [ ! -d "venv" ]; then
    echo "Setting up Python virtual environment..."
    python3 -m venv venv
    source venv/bin/activate
    pip install --upgrade pip
    pip install -r requirements.txt
else
    source venv/bin/activate
fi

# Run the plotting script
echo "Generating plots..."
python plots.py

echo "=== Build and Run Complete ==="
echo "Trajectory data saved to docs/trajectory.txt"
echo "Plot saved to docs/trajectory.png"

# Deactivate virtual environment
# deactivate 