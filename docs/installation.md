# Installation Guide

## 1. Cloning the Repository

To start, clone the UltiBlox repository to your local machine:

```bash
git clone git@github.com:UltiBlox/UltiBloxExamples.git
cd UltiBlox
```

## 2. Running the Prepare Script (for Library Installation)

The **prepare.sh** script will automatically install the required libraries for the project, so you don't need to manually install them.

1. Run the `prepare.sh` script:

   ```bash
   bash prepare.sh
   ```

This will install the Arduino CLI (if not already installed) and ensure all necessary libraries are added to your Arduino `libraries` folder.

## 3. Installation Modes

### Direct Clone into Arduino Libraries Folder (Simple Install)

This is the **easiest option** if you want to use the project without making any modifications.

1. **Install Git** (if not installed):

   ```bash
   sudo apt update
   sudo apt install git
   ```

2. **Clone the Repository Directly into Arduino Libraries Folder**:

   ```bash
   git clone git@github.com:UltiBlox/UltiBloxExamples.git ~/Arduino/libraries/UltiBlox
   ```

3. **Run the Prepare Script** to install any missing libraries:

   ```bash
   cd ~/Arduino/libraries/UltiBlox
   bash prepare.sh
   ```

The project is now installed and ready for use in the Arduino IDE.

### Cloning to a Workspace (For Development or Customization)

If you're planning to **customize or develop** the project, you should clone it to a workspace outside the Arduino folder. Then, choose between these two options:

#### a. Symlink Mode (For Active Development)

This mode is best for developers who need to modify the project and test changes without copying files.

1. **Clone the Project to a Workspace**:

   ```bash
   git clone git@github.com:UltiBlox/UltiBloxExamples.git ~/workspace/UltiBlox
   cd ~/workspace/UltiBlox
   ```

2. **Create a Symlink to Arduino Libraries Folder**:

   ```bash
   bash install-symlink.sh
   ```

This links the project to the Arduino libraries folder without copying, so you can edit the project and see changes immediately.

#### b. Standard Installation (Copy Mode)

If you're not actively developing but want to install the project from a workspace, use this method.

1. **Clone the Project to a Workspace**:

   ```bash
   git clone git@github.com:UltiBlox/UltiBloxExamples.git ~/workspace/UltiBlox
   cd ~/workspace/UltiBlox
   ```

2. **Run the Install Script** to copy the project into the Arduino libraries folder:

   ```bash
   bash install.sh
   ```

## 4. Compiling and Uploading

### Using the Arduino IDE

1. Open the Arduino IDE and navigate to `File > Open`, then select the example sketch (e.g., `SensorControl.ino`).
2. Install any missing libraries as prompted by the IDE.
3. Select the appropriate board (e.g., Arduino Nano) and COM port under `Tools > Board` and `Tools > Port`.
4. Compile and upload the sketch to your Arduino board.

### Using Arduino CLI

If you prefer to use the Arduino CLI, you can compile and upload the sketch with the following commands:

```bash
arduino-cli compile --fqbn arduino:avr:nano examples/SensorControl/SensorControl.ino
arduino-cli upload -p /dev/ttyUSB0 --fqbn arduino:avr:nano examples/SensorControl/SensorControl.ino
```

Be sure to replace `/dev/ttyUSB0` with the appropriate port for your board.

## 5. Troubleshooting

If you encounter issues, ensure the libraries are properly installed and that the correct board is selected in the Arduino IDE.

- [Overview](overview.md)
- [Libraries](libraries.md)
- [Examples](examples.md)
