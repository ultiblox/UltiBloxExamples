#!/bin/bash

set -e
# Set the system-wide installation directory for Arduino CLI
BINDIR="/usr/local/bin"
CLI_VERSION="latest"  # Change to a specific version if needed

# Check if arduino-cli is already installed
if command -v arduino-cli &> /dev/null; then
    echo "Arduino CLI is already installed."
else
    echo "Installing Arduino CLI system-wide to $BINDIR..."

    # Download and install Arduino CLI with sudo permissions
    curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sudo BINDIR=$BINDIR sh -s $CLI_VERSION

    # Check if the installation was successful
    if [ $? -ne 0 ]; then
        echo "Error: Arduino CLI installation failed."
        exit 1
    else
        echo "Arduino CLI installed successfully in $BINDIR."
    fi
fi

# Verify the installation
arduino-cli version

# Install the Arduino AVR Core
arduino-cli core update-index
arduino-cli core install arduino:avr || {
    echo "Error: Failed to install arduino:avr core."
    exit 1
}

