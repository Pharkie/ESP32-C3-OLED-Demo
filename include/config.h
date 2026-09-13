#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <qrcode.h>

//! =============================================================================
// DISPLAY DRIVER CONFIG
// Define USE_SSD1306 for SSD1306
// Define USE_SH1106 for SH1106
// Only uncomment ONE of the following lines to select the display driver!
// =============================================================================
#define USE_SSD1306
// #define USE_SH1106
//! =============================================================================

#if defined(USE_SSD1306)
#include <Adafruit_SSD1306.h>
extern Adafruit_SSD1306 display;
// Display offset for 72x40 visible area in 128x64 buffer:
// Horizontal: (128 - 72) / 2 = 28
// Vertical: 24 to properly center the 72x40 display
#ifndef SCREEN_OFFSET_X
#define SCREEN_OFFSET_X 28
#endif
#ifndef SCREEN_OFFSET_Y
#define SCREEN_OFFSET_Y 24
#endif
#else // SH1106
#include <Adafruit_SH110X.h>
extern Adafruit_SH1106G display;
#ifndef SCREEN_OFFSET_X
#define SCREEN_OFFSET_X 26 // X offset through trial and error
#endif
#ifndef SCREEN_OFFSET_Y
#define SCREEN_OFFSET_Y 24 // Y offset through trial and error
#endif
#endif

// Fix definitions for SSD1306 compatibility
#ifndef SH110X_BLACK
#define SH110X_BLACK 0
#endif
#ifndef SH110X_WHITE
#define SH110X_WHITE 1
#endif

// OLED display configuration
#define SCREEN_WIDTH 128    // Declare as 128x64 even though actual is 72x40
#define SCREEN_HEIGHT 64    // This works better with offset
#define OLED_RESET -1       // Reset pin (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // I2C address

// Actual usable screen dimensions
#define ACTUAL_WIDTH 72
#define ACTUAL_HEIGHT 40

// ESP32-C3 pins
#define SDA_PIN 5  // I2C Data
#define SCL_PIN 6  // I2C Clock
#define LED_PIN 8  // Onboard LED
#ifndef BOOT_PIN
#define BOOT_PIN 9 // Boot button
#endif

// QR Code configuration
#define QR_CODE_URL "https://github.com/Pharkie/ESP32-C3-OLED-Demo"

#endif // CONFIG_H
