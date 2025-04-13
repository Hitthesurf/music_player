#!/bin/bash
# Quit on any error
set -e

# Check if an argument is provided
if [ -z "$1" ]; then
    echo "Error: No preset name provided."
    echo "Usage: $0 <preset-name>"
    exit 1
fi

preset_name="$1"

pushd ..

echo ">>> Building Project Compile Commands"
cmake --preset="$preset_name" --fresh

echo ">>> Running Clang-Tidy Command"
python3 scripts/external/run-clang-tidy.py -p build/vs.${preset_name} -source-filter "^(?!.*\.cc$).*" -warnings-as-errors="*"

popd