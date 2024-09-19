#!/bin/bash

# Set the system-wide installation directory for Arduino CLI
BINDIR="/usr/local/bin"

# Check if arduino-cli is already installed
if command -v arduino-cli &> /dev/null; then
    echo "Arduino CLI is already installed."
else
    echo "Installing Arduino CLI system-wide to $BINDIR..."

    # Download and install Arduino CLI with sudo permissions
    curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sudo BINDIR=$BINDIR sh

    # Check if the installation was successful
    if [ $? -ne 0 ]; then
        echo "Error: Arduino CLI installation failed."
        exit 1
    else
        echo "Arduino CLI installed successfully in $BINDIR."
    fi
fi

# Clone and install custom libraries manually
bash prepare-libraries.sh

# Install remaining libraries through Arduino CLI
arduino-cli lib install "EasyButton"
arduino-cli lib install "SensorAnalog"

# Verify installed libraries
arduino-cli lib list
