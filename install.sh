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

# Install the main library
if [ "$(pwd)" == "$ARDUINO_LIBRARIES_DIR/$LIBRARY_NAME" ]; then
    echo "$LIBRARY_NAME is already installed in Arduino libraries folder."
else
    cp -r "$(pwd)" "$ARDUINO_LIBRARIES_DIR/$LIBRARY_NAME"
    echo "$LIBRARY_NAME installed successfully to $ARDUINO_LIBRARIES_DIR"
fi

# Process dependencies
DEPENDENCIES_FILE="./dependencies.txt"

if [ ! -f "$DEPENDENCIES_FILE" ]; then
    echo "No dependencies file found. Skipping dependency installation."
    exit 0
fi

while IFS=',' read -r DEP_NAME GIT_URL || [ -n "$DEP_NAME" ]; do
    DEP_NAME=$(echo "${DEP_NAME}" | tr -d '\r' | sed 's/^[ \t]*//;s/[ \t]*$//')
    GIT_URL=$(echo "${GIT_URL}" | tr -d '\r' | sed 's/^[ \t]*//;s/[ \t]*$//')

    if [ -z "$DEP_NAME" ]; then
        echo "Skipping empty or invalid line in dependencies.txt."
        continue
    fi

    if [ -z "$GIT_URL" ]; then
        # Install via Arduino CLI
        echo "Installing Arduino library: $DEP_NAME using Arduino CLI..."
        arduino-cli lib install "$DEP_NAME" || {
            echo "Error: Failed to install Arduino library $DEP_NAME"
            exit 1
        }
    else
        # Handle sibling libraries
        DEP_PATH="$(dirname "$(pwd)")/$DEP_NAME"

        if [ ! -d "$DEP_PATH" ]; then
            echo "Error: Dependency $DEP_NAME is missing. Please run prepare-libraries.sh first."
            exit 1
        fi

        echo "Installing dependency: $DEP_NAME"
        if [ -f "$DEP_PATH/install.sh" ]; then
            (cd "$DEP_PATH" && bash "install.sh") || {
                echo "Error: Failed to install dependency $DEP_NAME"
                exit 1
            }
        else
            echo "Warning: install.sh not found for $DEP_NAME. Skipping."
        fi
    fi
done < "$DEPENDENCIES_FILE"

echo "$LIBRARY_NAME and its dependencies installed successfully."

