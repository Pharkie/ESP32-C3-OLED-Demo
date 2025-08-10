# ESP32-C3 OLED Hello World Demo

A PlatformIO project to display "Hello World" on an ESP32-C3 development board
with a 0.42 inch OLED display.

## Hardware Requirements

- ESP32-C3 Development Board with onboard 0.42" OLED display
- The OLED is typically connected via I2C on pins GPIO8 (SDA) and GPIO9 (SCL)

## PlatformIO Setup

This project uses PlatformIO for development. Libraries are automatically
managed through `platformio.ini`.

### Required Libraries (Auto-installed):

1. **Adafruit SSD1306** - OLED display driver
2. **Adafruit GFX Library** - Graphics library
3. **Wire** - Built-in I2C library

### Quick Start:

1. Make sure you have PlatformIO extension installed in VS Code
2. Open this folder in VS Code
3. PlatformIO will automatically install dependencies
4. Build and upload using PlatformIO commands

## Pin Configuration

The sketch is configured for common ESP32-C3 OLED board pinouts:

- **SDA (Data)**: GPIO8
- **SCL (Clock)**: GPIO9
- **OLED Address**: 0x3C (standard for most 128x64 OLED displays)

If your board uses different pins, modify these lines in the code:

```cpp
#define SDA_PIN 8
#define SCL_PIN 9
```

## Features

- Displays "Hello World" with blinking animation
- Shows uptime counter
- Includes both simple and centered text display functions
- Serial output for debugging
- Error handling for OLED initialization

## How to Use

1. **Open in VS Code with PlatformIO**:

   - Make sure PlatformIO extension is installed
   - Open this project folder in VS Code
   - PlatformIO will detect the `platformio.ini` file

2. **Build the project**:

   - Use Ctrl+Shift+P (Cmd+Shift+P on Mac) → "PlatformIO: Build"
   - Or click the checkmark icon in the PlatformIO toolbar

3. **Upload to ESP32-C3**:

   - Connect your ESP32-C3 board via USB
   - Use Ctrl+Shift+P → "PlatformIO: Upload"
   - Or click the arrow icon in the PlatformIO toolbar

4. **Monitor Serial Output**:
   - Use Ctrl+Shift+P → "PlatformIO: Serial Monitor"
   - Or click the plug icon in the PlatformIO toolbar
   - Baud rate is set to 115200

## PlatformIO Commands

- **Build**: `pio run`
- **Upload**: `pio run --target upload`
- **Serial Monitor**: `pio device monitor`
- **Clean**: `pio run --target clean`

## Troubleshooting

### OLED Not Working:

- Check I2C connections (SDA/SCL pins)
- Verify OLED address (try 0x3D if 0x3C doesn't work)
- Ensure proper power supply to the OLED
- Check Serial Monitor for error messages

### Common OLED Addresses:

- `0x3C` - Most common for 128x64 displays
- `0x3D` - Alternative address for some displays

### Pin Variations:

Some ESP32-C3 boards may use different I2C pins:

- GPIO4 (SDA), GPIO5 (SCL)
- GPIO21 (SDA), GPIO22 (SCL)

Check your board's documentation for the correct pins.

## Code Structure

- `setup()`: Initializes serial, I2C, and OLED display
- `loop()`: Creates blinking animation
- `displayHelloWorld()`: Main display function with uptime
- `displayCenteredHelloWorld()`: Alternative centered text display

## Next Steps

Try modifying the code to:

- Display sensor readings
- Add graphics and shapes
- Create different text animations
- Show Wi-Fi status
- Display time and date
