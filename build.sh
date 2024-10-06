#!/bin/bash

# Set the board type (e.g., arduino:avr:uno or esp32:esp32:esp32)
BOARD_TYPE="arduino:avr:uno"

# Check if arduino-cli is installed
if ! command -v arduino-cli &> /dev/null
then
    echo "arduino-cli not found. Please install it from https://arduino.github.io/arduino-cli/installation/"
    exit 1
fi

# Loop through all example sketches in the examples/ directory
EXAMPLES_DIR="examples"
for example in "$EXAMPLES_DIR"/*; do
    if [ -d "$example" ]; then
        example_name=$(basename "$example")
        sketch="$example/$example_name.ino"

        if [ -f "$sketch" ]; then
            echo "Compiling example: $sketch"
            arduino-cli compile --fqbn "$BOARD_TYPE" --libraries "$HOME/Arduino/libraries" "$sketch"

            # Check if the compilation was successful
            if [ $? -eq 0 ]; then
                echo "Build successful for $sketch"
            else
                echo "Build failed for $sketch"
                exit 1
            fi
        else
            echo "No .ino file found in $example"
        fi
    fi

done

echo "All examples compiled successfully."