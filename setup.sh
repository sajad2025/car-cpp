#!/bin/bash

# Exit on error
set -e

# Create virtual environment if it doesn't exist
if [ ! -d "venv" ]; then
    echo "Creating virtual environment..."
    python3 -m venv venv
fi

# Install required packages
echo "Installing required packages..."
source venv/bin/activate
pip install --upgrade pip
pip install matplotlib numpy

echo ""
echo "Setup complete!"
echo ""
echo "To activate the virtual environment in your current shell, run:"
echo ""
echo "  source venv/bin/activate"
echo ""
echo "After activation, you can run the plotting script with:"
echo "  python plots.py"
echo ""
echo "To deactivate the virtual environment when finished, run:"
echo "  deactivate"
echo ""

# Provide a direct way to activate the environment in the current shell
# This is the key part that allows the environment to persist
if [[ "$0" == "${BASH_SOURCE[0]}" ]]; then
    # Script is being executed, not sourced
    echo "For automatic activation, run this script with 'source':"
    echo ""
    echo "  source setup.sh"
    echo ""
else
    # Script is being sourced, so we can activate the environment
    echo "Activating virtual environment..."
    # We're already in the activated environment from above
    echo "Virtual environment is now active. You can run:"
    echo "  python plots.py"
    echo ""
fi 