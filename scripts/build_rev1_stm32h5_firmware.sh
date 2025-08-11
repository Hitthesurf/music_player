#!/bin/bash
# Quit on any error
set -e

pushd ..

# Run CMake with the specified preset
cmake --preset="firmware-rev1" --fresh
cmake --build --preset="firmware-rev1"

popd