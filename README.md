# ESP32-C3 OLED Demo (C++)

A little demo project to display tests on an ESP32-C3 development board with an
onboard 0.42 inch OLED display (see pic).

Written in C++ and using Arduino libraries in VS Code. Not Arduino IDE so there
isn't a .ino file. Not Micropython.

<table>
<tr>
<td><img src="ESP-OLED-test.gif" alt="Demo Animation" width="400"/></td>
<td><img src="Device_image.png" alt="ESP32-C3 OLED Development Board" width="400"/></td>
</tr>
</table>

## Hardware Requirements

- ESP32-C3 Development Board with onboard 0.42" OLED display (72x40 pixels)

## Features

The demo cycles across 9 different display tests, changing every 2 seconds:

1. **Pixel Test** - Shows pixel addressing with crosshairs and coordinate info
2. **Border Test** - Full border with corner marker pixels and dimension display
3. **Pattern Test** - Checkerboard pattern with inverted text overlay
4. **Scroll Test** - Animated scrolling text with moving indicator
5. **Bar Graph** - Animated sine wave bar chart
6. **Shapes Test** - Expanding circle animation with triangles
7. **Line Pattern** - Moving diagonal and vertical line animations
8. **Gradient Test** - Dithered gradient effect using pixel patterns
9. **QR Code** - Links to this GitHub repository (scannable with QR apps)

## Pre-built Firmware

Flash the pre-built firmware :

### Option 1: Using esptool.py

```bash
# Install esptool
pip install esptool

# Flash the firmware (replace /dev/ttyUSB0 with your port)
esptool.py --chip esp32c3 --port /dev/ttyUSB0 --baud 460800 write_flash 0x10000 firmware.bin

# On macOS, port might be something like /dev/cu.usbmodem1101
# On Windows, port might be COM3, COM4, etc.
```

### Option 2: Using Web-based ESP32 Flasher

You can use online ESP32 flashing tools that work directly in Chrome/Edge
browsers:

- **ESP Web Tools**:
  [https://esphome.github.io/esp-web-tools/](https://esphome.github.io/esp-web-tools/)
- **ESP Tool Online**:
  [https://espressif.github.io/esptool-js/](https://espressif.github.io/esptool-js/)

1. **Download firmware.bin** from
   [Releases](https://github.com/Pharkie/ESP32-C3-OLED-Demo/releases)
2. **Open web flasher** in Chrome or Edge browser with Web Serial API support.
3. **Connect ESP32-C3** via USB
4. **Select firmware.bin** and flash at address `0x10000`

### Option 3: Using ESP32 Flash Download Tool

1. **Download firmware**: Get `firmware.bin` from
   [Releases](https://github.com/Pharkie/ESP32-C3-OLED-Demo/releases)
2. **Install ESP32 Flash Tool**: Download from
   [Espressif](https://www.espressif.com/en/support/download/other-tools)
3. **Flash settings**:
   - **Chip Type**: ESP32-C3
   - **firmware.bin** at address `0x10000`
   - **Boot Mode**: UART
   - **Flash Size**: 4MB
4. **Connect ESP32-C3** via USB and click "START"

## Development Setup

You can modify the code or build from source using VS Code / PlatformIO.

### Required Libraries Auto-installed by PlatformIO:

1. **Adafruit SH110X** - SH1106 OLED display driver (works better than SSD1306)
2. **Adafruit GFX Library** - Graphics library for drawing functions
3. **QRCode** - QR code generation library
4. **Wire** - Built-in I2C library

### Setup Steps:

1. Make sure you have PlatformIO extension installed in VS Code
2. Fork or clone the Git repo and open this folder in VS Code
3. PlatformIO will automatically install dependencies
4. Build and upload using PlatformIO commands

## Code Structure

The code is organized into modular files:

```
├── include/
│   ├── config.h           # Hardware configuration and constants
│   ├── display_helpers.h  # Helper function declarations
│   └── display_tests.h    # Test function declarations
├── src/
│   ├── main.cpp          # Main program logic
│   ├── display_helpers.cpp # Abstracted display functions
│   ├── test_pixel.cpp    # Pixel addressing test
│   ├── test_border.cpp   # Border test
│   ├── test_pattern.cpp  # Pattern test
│   ├── test_scroll.cpp   # Scrolling text test
│   ├── test_bargraph.cpp # Bar graph animation
│   ├── test_shapes.cpp   # Circle and shapes test
│   ├── test_lines.cpp    # Line pattern animations
│   ├── test_gradient.cpp # Gradient dithering test
│   └── test_qrcode.cpp   # QR code generation
└── platformio.ini        # Project configuration
```

## Configuration Tips

The project is configured for the specific ESP32-C3 OLED board pinout:

- **SDA (Data)**: GPIO5
- **SCL (Clock)**: GPIO6
- **LED**: GPIO8 (onboard LED for error indication)
- **OLED Address**: 0x3C (standard for SH1106 displays)
- **Display Size**: 72x40 pixels (declared as 128x64 with offset for
  compatibility)

The display uses a calibrated offset (X=26, Y=24) to properly center content on
the 72x40 screen. You may need to adjust the offset on your device.

Modify config values in `include/config.h`:

```cpp
#define SDA_PIN 5
#define SCL_PIN 6
#define SCREEN_OFFSET_X 26
#define SCREEN_OFFSET_Y 24
```

## QR Code

The QR code test generates a scannable code linking to this GitHub repository:

**Scanning Tips:**

- Use dedicated QR scanner apps rather than iPhone camera
- Turn OFF macro mode for better recognition
- Hold phone 12 inches away.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file
for details.
