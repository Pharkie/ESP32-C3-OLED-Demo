#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <qrcode.h>

// OLED display configuration
#define SCREEN_WIDTH 128    // Declare as 128x64 even though actual is 72x40
#define SCREEN_HEIGHT 64    // This works better with offset
#define OLED_RESET -1       // Reset pin (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // I2C address

// Display offset for 72x40 screen declared as 128x64
#define SCREEN_OFFSET_X 26 // X offset through trial and error
#define SCREEN_OFFSET_Y 24 // Y offset through trial and error

// Actual usable screen dimensions
#define ACTUAL_WIDTH 72
#define ACTUAL_HEIGHT 40

// ESP32-C3 pins
#define SDA_PIN 5  // I2C Data
#define SCL_PIN 6  // I2C Clock
#define LED_PIN 8  // Onboard LED
#define BOOT_PIN 9 // Boot button

// External display object reference
extern Adafruit_SH1106G display;

#endif // CONFIG_H
