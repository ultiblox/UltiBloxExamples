#!/bin/bash

# Run preparation scripts for Arduino CLI and libraries
bash prepare-arduino-cli.sh || {
    echo "Error: Arduino CLI preparation failed."
    exit 1
}

bash prepare-libraries.sh || {
    echo "Error: Libraries preparation failed."
    exit 1
}

