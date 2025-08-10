/*
 * ESP32-C3 OLED Hello World Demo
 *
 * This sketch displays "Hello World" on a 0.42 inch OLED display
 * connected to an ESP32-C3 development board.
 *
 * PlatformIO Libraries (automatically installed via platformio.ini):
 * - adafruit/Adafruit SH110X (SH1106 driver works better than SSD1306)
 * - adafruit/Adafruit GFX Library
 * - ricmoo/QRCode (for QR code generation)
 * - Wire (built-in Arduino library for I2C)
 *
 * Hardware:
 * - ESP32-C3 Development Board with onboard 0.42" OLED (72x40 pixels)
 * - Pinout: SCL=GPIO6, SDA=GPIO5, LED=GPIO8, Boot Button=GPIO9
 * - Even though screen is 72x40, declare as 128x64 with offset (X=26, Y=24)
 */

#include "config.h"
#include "display_tests.h"

// Create display object for SH1106
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
    // Initialize serial communication for debugging
    Serial.begin(115200);

    // Wait for serial port to connect (useful for debugging)
    while (!Serial)
    {
        delay(10);
    }

    Serial.println("ESP32-C3 OLED Hello World Demo (SH1106)");

    // Initialize LED pin
    pinMode(LED_PIN, OUTPUT);

    // Initialize I2C with custom pins
    Wire.begin(SDA_PIN, SCL_PIN);

    // Initialize the OLED display with SH1106 driver
    if (!display.begin(SCREEN_ADDRESS, true)) // true = reset display
    {
        Serial.println(F("SH1106 allocation failed"));
        for (;;)
        {
            // Don't proceed, loop forever - blink LED to indicate error
            digitalWrite(LED_PIN, HIGH);
            delay(500);
            digitalWrite(LED_PIN, LOW);
            delay(500);
            Serial.println("OLED initialization failed - check connections!");
        }
    }

    Serial.println("SH1106 OLED initialized successfully!");

    // Clear the display buffer
    display.clearDisplay();

    // Show initial display buffer contents on the screen
    display.display();
    delay(1000);

    // Display pixel test
    displayPixelTest();
}

void loop()
{
    // // Just display QR code (comment out cycling for testing)
    // displayQRCode();
    // delay(100);

    // Cycle through different test patterns
    static uint8_t testMode = 0;
    static unsigned long lastChange = 0;

    if (millis() - lastChange > 2000)
    { // Change every 2 seconds (faster cycling)
        lastChange = millis();
        testMode = (testMode + 1) % 9; // Now 9 different tests
    }

    switch (testMode)
    {
    case 0:
        displayPixelTest();
        break;
    case 1:
        displayBorderTest();
        break;
    case 2:
        displayPatternTest();
        break;
    case 3:
        displayScrollText();
        break;
    case 4:
        displayBarGraph();
        break;
    case 5:
        displayCircleTest();
        break;
    case 6:
        displayLinePattern();
        break;
    case 7:
        displayGradientTest();
        break;
    case 8:
        displayQRCode();
        break;
    }

    delay(50);
}
