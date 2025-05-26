#!/bin/bash
set -e

pushd ..
# List of directories to exclude (space-separated)
EXCLUDE_DIRS=("build" "firmware/**/drivers/**/device" "targets" "waveforms")

# List of file extensions to check (space-separated)
FILE_EXTENSIONS=("cpp" "c" "h" "hpp")

# Build the find command dynamically
COMMAND="find . \("

# Add directory exclusions
for dir in "${EXCLUDE_DIRS[@]}"; do
    COMMAND+=" -path '*/$dir' -o"
done
COMMAND=${COMMAND::-2}

# Add file extension conditions
COMMAND+="\) -prune -o \("
first=true
for ext in "${FILE_EXTENSIONS[@]}"; do
    if [ "$first" = true ]; then
        COMMAND+=" -name '*.$ext'"
        first=false
    else
        COMMAND+=" -o -name '*.$ext'"
    fi
done
COMMAND+=" \) -exec clang-format --dry-run --Werror {} +"

# Execute the final command
echo $COMMAND
eval "$COMMAND"

popd