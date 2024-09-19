#!/bin/bash

# Function to clone libraries if not already present and run their prepare scripts
install_library() {
  local LIBRARY_NAME="$1"
  local LIBRARY_PATH="$HOME/Arduino/libraries/$LIBRARY_NAME"
  local GIT_URL="$2"

  if [ ! -d "$LIBRARY_PATH" ]; then
    echo "Cloning $LIBRARY_NAME into Arduino libraries folder..."
    git clone "$GIT_URL" "$LIBRARY_PATH"
  else
    echo "$LIBRARY_NAME already exists, skipping clone."
  fi

  # Run prepare.sh if it exists
  if [ -f "$LIBRARY_PATH/prepare.sh" ]; then
    echo "Running $LIBRARY_NAME prepare script..."
    bash "$LIBRARY_PATH/prepare.sh"
  else
    echo "No prepare script found for $LIBRARY_NAME."
  fi
}

# Install all necessary libraries
install_library "LCDI2C" "https://github.com/makers-multiverse/LCDI2C.git"
install_library "SensorAnalog" "https://github.com/makers-multiverse/SensorAnalog.git"
install_library "DisplayValueCommon" "https://github.com/makers-multiverse/DisplayValueCommon.git"
install_library "DisplayValueLCD" "https://github.com/makers-multiverse/DisplayValueLCD.git"
install_library "DisplayValueOLED" "https://github.com/makers-multiverse/DisplayValueOLED.git"

# Finish
echo "Library preparation complete."
