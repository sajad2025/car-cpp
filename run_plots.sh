#!/bin/bash
# Get the directory of this script
SCRIPT_DIR="$( cd "$( dirname "${0}" )" && pwd )"
source "$SCRIPT_DIR/venv/bin/activate"
python "$SCRIPT_DIR/plots.py" "$@"
echo "When finished with the virtual environment, run 'deactivate'."
