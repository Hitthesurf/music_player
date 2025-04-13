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

build_dir=build/vs.$preset_name
covarage_dir=build/coverage

pushd ..
rm -rf $covarage_dir

echo ">>> Building Project unit tests"

# Make sure coverage flags are passed
cmake --preset="$preset_name" --fresh
cmake --build --preset="$preset_name"


echo ">>> Running Project unit tests"
ctest --preset="$preset_name" --schedule-random --extra-verbose --output-log "Logs/${preset_name}.log" || true

# Make Coverage Directory
mkdir $covarage_dir

# Run lcov
lcov --directory $build_dir --base-directory . --capture --output-file $covarage_dir/coverage_raw.info
lcov --remove $covarage_dir/coverage_raw.info '*/tests/*' '*/build/*' '*/usr/*' --output-file $covarage_dir/coverage.info

# Generate HTML Coverage Report
genhtml --demangle-cpp -o $covarage_dir/coverage_website $covarage_dir/coverage.info --prefix $(pwd)

popd
