#!/bin/bash
# Quit on any error
set -e

pushd ..

# Run CMake with the specified preset
cmake --preset="firmware-nucleo" --fresh
cmake --build --preset="firmware-nucleo"

popd