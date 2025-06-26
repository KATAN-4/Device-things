# Device-things

## English

Device-things is a simple Python tool that automatically detects the bootloader status of your Android device and helps you manage the bootloader lock.

### Features

- Automatic detection of the device when connected via USB  
- Display device model and serial number  
- Detect whether the device is in adb mode or bootloader (fastboot) mode  
- Check if the bootloader is locked or unlocked  
- Ask for user confirmation before rebooting to bootloader mode  
- Ask if you want to unlock the bootloader if it is locked (unlock command can be added)  
- Automatically download and setup platform-tools (adb, fastboot) for Windows, Linux, and macOS  
- Supports Turkish and English languages (auto-detect system language)

### Requirements

- Python 3.x  
- Internet connection (for automatic platform-tools download)

### Usage

1. Run the `main.py` script in your Python environment:

```bash
python3 main.py
