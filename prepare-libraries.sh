#!/bin/bash

# Define the Arduino libraries folder
LIBRARY_PATH1="$HOME/Arduino/libraries/LCDI2C"
LIBRARY_PATH2="$HOME/Arduino/libraries/SensorAnalog"

# Check if LCDI2C is already present
if [ ! -d "$LIBRARY_PATH1" ]; then
    echo "Cloning LCDI2C library into Arduino libraries folder..."
    git clone https://github.com/makers-multiverse/LCDI2C.git "$LIBRARY_PATH1"
else
    echo "LCDI2C library already exists, skipping clone."
fi

# Check if SensorAnalog is already present
if [ ! -d "$LIBRARY_PATH2" ]; then
    echo "Cloning SensorAnalog library into Arduino libraries folder..."
    git clone https://github.com/makers-multiverse/SensorAnalog.git "$LIBRARY_PATH2"
else
    echo "SensorAnalog library already exists, skipping clone."
fi

# Add other necessary libraries as required

echo "Library preparation complete."
