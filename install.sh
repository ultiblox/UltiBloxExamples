#!/bin/bash

# Define the Arduino libraries folder
ARDUINO_LIBRARIES_DIR="$HOME/Arduino/libraries"

# Check if the Arduino libraries folder exists
if [ ! -d "$ARDUINO_LIBRARIES_DIR" ]; then
    echo "Error: Arduino libraries directory not found at $ARDUINO_LIBRARIES_DIR"
    exit 1
fi

# Define the project folder name
LIBRARY_NAME="UltiBloxExamples"

# Check if running inside Arduino libraries directory
if [ "$(pwd)" == "$ARDUINO_LIBRARIES_DIR/$LIBRARY_NAME" ]; then
    echo "$LIBRARY_NAME is already installed in Arduino libraries folder."
else
    # Copy the entire project to the Arduino libraries folder
    cp -r "$(pwd)" "$ARDUINO_LIBRARIES_DIR/$LIBRARY_NAME"
    echo "$LIBRARY_NAME installed successfully to $ARDUINO_LIBRARIES_DIR"
fi
