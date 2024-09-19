#!/bin/bash

# Define the Arduino libraries folder
LIBRARY_PATH1="$HOME/Arduino/libraries/LCDI2C"

# Check if LCDI2C is already present
if [ ! -d "$LIBRARY_PATH1" ]; then
    echo "Cloning LCDI2C library into Arduino libraries folder..."
    git clone https://github.com/makers-multiverse/LCDI2C.git "$LIBRARY_PATH1"
else
    echo "LCDI2C library already exists, skipping clone."
fi

# Add other necessary libraries as required
# Example:
# LIBRARY_PATH2="$HOME/Arduino/libraries/EasyButton"
# Check if EasyButton is already present and clone

echo "Library preparation complete."
