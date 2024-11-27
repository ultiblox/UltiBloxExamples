#!/bin/bash

# Path to dependencies.txt
DEPENDENCIES_FILE="./dependencies.txt"
PARENT_DIR=$(dirname "$(pwd)")

# Ensure dependencies.txt exists
if [ ! -f "${DEPENDENCIES_FILE}" ]; then
  echo "Error: dependencies.txt not found."
  exit 1
fi

echo "Preparing sibling libraries for UltiBloxExamples..."

# Read and process each dependency from dependencies.txt
while IFS=',' read -r LIB_NAME GIT_URL || [ -n "$LIB_NAME" ]; do
  LIB_NAME=$(echo "${LIB_NAME}" | tr -d '\r' | sed 's/^[ \t]*//;s/[ \t]*$//')
  GIT_URL=$(echo "${GIT_URL}" | tr -d '\r' | sed 's/^[ \t]*//;s/[ \t]*$//')

  # Skip invalid or empty lines
  if [[ -z "$LIB_NAME" || -z "$GIT_URL" ]]; then
    echo "Skipping empty or invalid line"
    continue
  fi

  echo ""
  echo "Processing dependency: $LIB_NAME"
  echo "  Dependency of: UltiBloxExamples"

  DEP_PATH="$PARENT_DIR/$LIB_NAME"

  if [ ! -d "${DEP_PATH}" ]; then
    echo "Cloning $LIB_NAME into $PARENT_DIR..."
    git clone "$GIT_URL" "$DEP_PATH" || {
      echo "Error: Failed to clone $LIB_NAME. Skipping."
      continue
    }
  else
    echo "Updating $LIB_NAME..."
    git -C "$DEP_PATH" pull || {
      echo "Error: Failed to update $LIB_NAME. Skipping."
      continue
    }
  fi

  # Run the library's prepare.sh if it exists
  if [ -f "$DEP_PATH/prepare.sh" ]; then
    echo "Running prepare.sh for $LIB_NAME..."
    (cd "$DEP_PATH" && bash "prepare.sh") || {
      echo "Error: Failed to prepare $LIB_NAME. Skipping."
      continue
    }
  else
    echo "No prepare.sh found for $LIB_NAME. Skipping preparation."
  fi
done < "$DEPENDENCIES_FILE"

echo "Dependencies for UltiBloxExamples prepared successfully."