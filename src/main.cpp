/*
 * ESP32-C3 OLED Hello World Demo
 *
 * This sketch displays "Hello World" on a 0.42 inch OLED display
 * connected to an ESP32-C3 development board.
 *
 * PlatformIO Libraries (automatically installed via platformio.ini):
 * - adafruit/Adafruit SH110X
 * - adafruit/Adafruit SSD1306
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

// Create display object for selected driver
#if defined(USE_SSD1306)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#else
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#endif

void setup()
{
    delay(1000); // Wait for 1s
    // Initialize serial communication for debugging
    Serial.begin(115200);

    // Wait for serial port to connect (useful for debugging)
    while (!Serial)
    unsigned long startSerial = millis();
    while (!Serial && (millis() - startSerial < 1000))
    {
        delay(10);
    }
    delay(200);

#if defined(USE_SSD1306)
    Serial.println("ESP32-C3 OLED Hello World Demo (SSD1306)");
#else
    Serial.println("ESP32-C3 OLED Hello World Demo (SH1106)");
#endif

    // Initialize LED pin
    pinMode(LED_PIN, OUTPUT);

    // Initialize I2C with custom pins
    Wire.begin(SDA_PIN, SCL_PIN);

    // Initialize the OLED display
#if defined(USE_SSD1306)
    // SSD1306_SWITCHCAPVCC enables internal charge pump
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306 allocation failed"));
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
    Serial.println("SSD1306 OLED initialized successfully!");
#else
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
#endif

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
    // Echo serial data received
    if (Serial.available())
    {
        char c = Serial.read();
        Serial.print("Received: ");
        Serial.println(c);
    }

    // // Just display QR code (comment out cycling for testing)
    // displayQRCode();
    // delay(100);

    // Cycle through different test patterns
    static uint8_t testMode = 0;
    static unsigned long lastChange = 0;

    // QR code gets longer display time (4s) vs other tests (2s)
    unsigned long displayTime = (testMode == 8) ? 4000 : 2000;

    if (millis() - lastChange > displayTime)
    { // Change timing based on current test
        lastChange = millis();
        testMode = (testMode + 1) % 9; // Now 9 different tests
        Serial.print("Test: "); // Print current test to serial
        Serial.println(testMode);
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
