# Installation Guide for UltiBlox Examples

This guide provides instructions for installing the UltiBlox Examples library. You can install it via the Arduino Library Manager or manually for development and customization.

---

## Option 1: Install via Arduino Library Manager (Recommended)

1. Open the **Arduino IDE**.
2. Go to **Tools > Manage Libraries**.
3. Search for **UltiBlox-Examples** and click **Install**.
4. Access example sketches under **File > Examples > UltiBlox-Examples**.

---

## Option 2: Manual Installation (for Development and Customization)

### Step 1: Clone the Repository

Clone the repository to your workspace:

```bash
git clone git@github.com:UltiBlox/UltiBloxExamples.git ~/workspace/UltiBloxExamples
cd ~/workspace/UltiBloxExamples
```

### Step 2: Prepare the Environment

Run the `prepare.sh` script to set up `arduino-cli` and install necessary libraries:

```bash
bash prepare.sh
```

### Step 3: Install the Library

To make `UltiBlox-Examples` accessible in the Arduino IDE, use one of the following scripts:

- **Copy Installation**:
  ```bash
  bash install.sh
  ```

- **Symlink Installation** (for active development):
  ```bash
  bash install-symlink.sh
  ```

### Step 4: Build and Compile Examples

To compile all examples, use the `build.sh` script:

```bash
bash build.sh
```

---

## Troubleshooting

- **Library Not Detected**: Ensure the Arduino IDE is restarted after running installation scripts.
- **Arduino CLI Not Found**: The `prepare.sh` script will install it if needed. For manual installation, see [Arduino CLI installation](https://arduino.github.io/arduino-cli/installation/).
