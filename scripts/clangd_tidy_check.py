## Compile Commands built in shell
import json
import shlex
import subprocess
import fnmatch
import argparse
import os

import time

PROJECT_BUILD_PREFIX = "/__w/music_player/music_player/build/vs.unit-tests." # CI path
# PROJECT_BUILD_PREFIX = "/workspaces/music_player/build/vs.unit-tests."     # Code spaces Path
EXTENSIONS = ["*.cpp", "*.c"]
EXCLUDE_PATTERNS = [
    "*/mocks/device/*"
]
# Note: Change to "1" to run in single thread
THREADS = 4


def compile_commands_database(preset):
    compile_commands_file_path = f"{PROJECT_BUILD_PREFIX}{preset}/compile_commands.json"
    with open(compile_commands_file_path, "r") as compile_commands_file:
        compile_db = json.load(compile_commands_file)
    return compile_db


def source_files_in_compile_commands(preset):
    compile_db = compile_commands_database(preset)

    source_files = []
    for section in compile_db:
        file_path = section["file"]
        if any(fnmatch.fnmatch(file_path, pattern) for pattern in EXTENSIONS):
            source_files.append(file_path)

    return source_files


def build_header_command(commands, file):
    header_command = "g++"
    for command in commands.split(" "):
        if "-I" in command:
            header_command += " " + command
    header_command += " -MM " + file.replace("\\", "/")
    return header_command


def format_header_command_stdout(stdout):
    # Remove backslash at end
    stdout = stdout.replace("\\", "")

    # Simplify path
    stdout = os.path.normpath(stdout)

    # List
    stdout = stdout.split("\n")

    # Only interested in header section
    return stdout[2:-1]


def add_to_list_unique(items_to_add: list[str], all_items: list[str]):
    for item in items_to_add:
        if item.strip() in all_items:
            continue
        all_items.append(item.strip())


def header_files_included_in_compile_commands(preset):
    compile_db = compile_commands_database(preset)

    all_header_files = []
    for section in compile_db:
        source_file_path = section["file"]
        if any(fnmatch.fnmatch(source_file_path, pattern) for pattern in EXTENSIONS):
            # Find all headers needed for the source file
            header_command = build_header_command(section["command"], section["file"])
            # Run header command
            args = shlex.split(header_command)
            result = subprocess.run(args, capture_output=True, text=True)

            header_files = format_header_command_stdout(result.stdout)
            add_to_list_unique(header_files, all_header_files)

    return all_header_files


def build_clangd_tidy_command(preset, files):
    command = f"clangd-tidy -j {THREADS} -p {PROJECT_BUILD_PREFIX}{preset} "
    for file in files:
        command += file
        command += " "
    return command


def filter_files(files, exclude_patterns):
    filtered = []
    for path in files:
        if any(fnmatch.fnmatch(path, pattern) for pattern in exclude_patterns):
            continue
        filtered.append(path)
    return filtered


def main():
    start = time.time()

    parser = argparse.ArgumentParser(description="Clang tidy check.")
    parser.add_argument(
        "preset",
        nargs="?",
        default=".",
        help="The name of the preset, used to find compile commands",
    )
    parser.add_argument("-v", "--verbose", action="count", default=0)
    args = parser.parse_args()

    # Get all cpp and c files in build
    source_files = source_files_in_compile_commands(args.preset)

    # Get all headers used in project
    header_files = header_files_included_in_compile_commands(args.preset)

    # Remove unwanted files
    files = filter_files(
        files=[*source_files, *header_files], exclude_patterns=EXCLUDE_PATTERNS
    )

    print(f"Files To Check: {len(files)}")
    # Create clangd tidy command
    command = build_clangd_tidy_command(args.preset, files)
    print("Command: -------")
    print(command)

    end = time.time()
    print(f"Took {end - start:.2f} seconds to build command")
    start = time.time()

    # Run clangd tidy command
    args = shlex.split(command)
    result = subprocess.run(args, capture_output=True, text=True)

    print("Result: --------")
    print(result.stdout)

    print("Error: ---------")
    print(result.stderr)

    end = time.time()
    print(f"Took {end - start:.2f} seconds")

    failed = (len(result.stdout) > 0) or (len(result.stderr) > 0)
    if failed:
        exit(1)


if __name__ == "__main__":
    main()
