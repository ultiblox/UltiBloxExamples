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

# Symlink the main library
if [ -L "$ARDUINO_LIBRARIES_DIR/$LIBRARY_NAME" ] || [ -d "$ARDUINO_LIBRARIES_DIR/$LIBRARY_NAME" ]; then
    echo "Symlink for $LIBRARY_NAME already exists."
else
    ln -s "$(pwd)" "$ARDUINO_LIBRARIES_DIR/$LIBRARY_NAME"
    echo "Symlink created for $LIBRARY_NAME at $ARDUINO_LIBRARIES_DIR"
fi

# Process dependencies
DEPENDENCIES_FILE="./dependencies.txt"

if [ ! -f "$DEPENDENCIES_FILE" ]; then
    echo "No dependencies file found. Skipping dependency symlinks."
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
        # Install Arduino CLI libraries
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

        echo "Symlinking dependency: $DEP_NAME"
        if [ -f "$DEP_PATH/install-symlink.sh" ]; then
            (cd "$DEP_PATH" && bash "install-symlink.sh") || {
                echo "Error: Failed to symlink dependency $DEP_NAME"
                exit 1
            }
        else
            echo "Warning: install-symlink.sh not found for $DEP_NAME. Skipping."
        fi
    fi
done < "$DEPENDENCIES_FILE"

echo "$LIBRARY_NAME and its dependencies symlinked successfully."

