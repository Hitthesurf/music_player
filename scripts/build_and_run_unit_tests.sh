#!/bin/bash
# Quit on any error
set -e

temp_unit_test_xml_dir=/tmp/unit_tests/

# Check if an argument is provided
if [ -z "$1" ]; then
    echo "Error: No preset name provided."
    echo "Usage: $0 <preset-name>"
    exit 1
fi

preset_name="$1"

pushd ..

# Run CMake with the specified preset
cmake --preset="$preset_name" --fresh
cmake --build --preset="$preset_name"

echo ">>> Running Project unit tests"
export GTEST_OUTPUT=xml:$temp_unit_test_xml_dir
rm -rf $temp_unit_test_xml_dir
ctest --preset="$preset_name" --schedule-random --extra-verbose --output-log "Logs/${preset_name}.log" --no-tests=error --timeout 5
cp $temp_unit_test_xml_dir*.xml Logs/

popd