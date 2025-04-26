#!/bin/bash

# Resolve directory of this script
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

INPUT_DIR="${SCRIPT_DIR}/inputs"
OUTPUT_DIR="${SCRIPT_DIR}/outputs"

rm -r "$OUTPUT_DIR"
echo "Removed old outputs directory: $OUTPUT_DIR"

mkdir -p "$OUTPUT_DIR"
echo "Created new outputs directory: $OUTPUT_DIR"

# Check the version of wireviz
wireviz --version

# Run wireviz on each input YAML file
wireviz $INPUT_DIR/* --output-dir "$OUTPUT_DIR"

# Remove any non-PNG files
find "$OUTPUT_DIR" -type f ! -name '*.png' -delete
