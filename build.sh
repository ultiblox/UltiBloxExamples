#!/bin/bash

# Set the board type (e.g., arduino:avr:uno or esp32:esp32:esp32)
BOARD_TYPE="arduino:avr:uno"

# Compile the Monitor.ino sketch using Arduino CLI
if ! command -v arduino-cli &> /dev/null
then
    echo "arduino-cli not found. Please install it from https://arduino.github.io/arduino-cli/installation/"
    exit 1
fi

# Compile the sketch
arduino-cli compile --fqbn $BOARD_TYPE --libraries "~/Arduino/libraries" src/Monitor

# Check if the compilation was successful
if [ $? -eq 0 ]; then
  echo "Build successful"
else
  echo "Build failed"
  exit 1
fi
