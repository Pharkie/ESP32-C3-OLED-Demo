/*
 * ESP32-C3 OLED Hello World Demo
 *
 * This sketch displays "Hello World" on a 0.42 inch OLED display
 * connected to an ESP32-C3 development board.
 *
 * PlatformIO Libraries (automatically installed via platformio.ini):
 * - adafruit/Adafruit SH110X (SH1106 driver works better than SSD1306)
 * - adafruit/Adafruit GFX Library
 * - Wire (built-in Arduino library for I2C)
 *
 * Hardware:
 * - ESP32-C3 Development Board with onboard 0.42" OLED (72x40 pixels)
 * - Pinout: SCL=GPIO6, SDA=GPIO5, LED=GPIO8, Boot Button=GPIO9
 * - Even though screen is 72x40, declare as 128x64 with offset (X=28, Y=12)
 */

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

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

// Create display object for SH1106
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Helper functions for abstracted display positioning
void setCursorActual(int16_t x, int16_t y);
void drawPixelActual(int16_t x, int16_t y, uint16_t color);
void drawLineActual(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
void drawRectActual(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void fillRectActual(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

void displayPixelTest();
void displayBorderTest();
void displayPatternTest();
void displayScrollText();
void displayBarGraph();
void displayCircleTest();
void displayLinePattern();
void displayGradientTest();

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
    // Cycle through different test patterns
    static uint8_t testMode = 0;
    static unsigned long lastChange = 0;

    if (millis() - lastChange > 2000)
    { // Change every 2 seconds (faster cycling)
        lastChange = millis();
        testMode = (testMode + 1) % 8; // Now 8 different tests
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
    }

    delay(50);
}

// Helper functions to abstract the offset - treat display as 72x40
void setCursorActual(int16_t x, int16_t y)
{
    display.setCursor(SCREEN_OFFSET_X + x, SCREEN_OFFSET_Y + y);
}

void drawPixelActual(int16_t x, int16_t y, uint16_t color)
{
    display.drawPixel(SCREEN_OFFSET_X + x, SCREEN_OFFSET_Y + y, color);
}

void drawLineActual(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
{
    display.drawLine(SCREEN_OFFSET_X + x0, SCREEN_OFFSET_Y + y0,
                     SCREEN_OFFSET_X + x1, SCREEN_OFFSET_Y + y1, color);
}

void drawRectActual(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    display.drawRect(SCREEN_OFFSET_X + x, SCREEN_OFFSET_Y + y, w, h, color);
}

void fillRectActual(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    display.fillRect(SCREEN_OFFSET_X + x, SCREEN_OFFSET_Y + y, w, h, color);
}

// Test all pixels by displaying a border around the entire 72x40 area
void displayBorderTest()
{
    display.clearDisplay();

    // Draw border around entire usable area
    drawRectActual(0, 0, ACTUAL_WIDTH, ACTUAL_HEIGHT, SH110X_WHITE);

    // Draw corner markers
    drawPixelActual(1, 1, SH110X_WHITE);
    drawPixelActual(ACTUAL_WIDTH - 2, 1, SH110X_WHITE);
    drawPixelActual(1, ACTUAL_HEIGHT - 2, SH110X_WHITE);
    drawPixelActual(ACTUAL_WIDTH - 2, ACTUAL_HEIGHT - 2, SH110X_WHITE);

    // Add text showing dimensions
    setCursorActual(2, 2);
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.print(F("72x40"));

    setCursorActual(2, 12);
    display.print(F("Border"));

    setCursorActual(2, 22);
    display.print(F("Test"));

    display.display();
}

// Test pattern with alternating pixels
void displayPatternTest()
{
    display.clearDisplay();

    // Draw checkerboard pattern
    for (int16_t y = 0; y < ACTUAL_HEIGHT; y += 2)
    {
        for (int16_t x = 0; x < ACTUAL_WIDTH; x += 2)
        {
            drawPixelActual(x, y, SH110X_WHITE);
            if (x + 1 < ACTUAL_WIDTH && y + 1 < ACTUAL_HEIGHT)
            {
                drawPixelActual(x + 1, y + 1, SH110X_WHITE);
            }
        }
    }

    // Add text overlay
    setCursorActual(2, 2);
    display.setTextSize(1);
    display.setTextColor(SH110X_BLACK, SH110X_WHITE); // Inverted text
    display.print(F("Pattern"));

    display.display();
}

// Test individual pixels and addressing
void displayPixelTest()
{
    display.clearDisplay();

    // Set text properties
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    setCursorActual(0, 0);

    // Display info about the screen
    display.print(F("72x40 Test"));
    setCursorActual(0, 10);
    display.print(F("Offset:"));
    display.print(SCREEN_OFFSET_X);
    display.print(F(","));
    display.print(SCREEN_OFFSET_Y);

    // Draw lines across the screen to test addressing
    drawLineActual(0, 20, ACTUAL_WIDTH - 1, 20, SH110X_WHITE);  // Horizontal line
    drawLineActual(36, 0, 36, ACTUAL_HEIGHT - 1, SH110X_WHITE); // Vertical line (center)

    // Test corner pixels
    drawPixelActual(0, 0, SH110X_WHITE);
    drawPixelActual(ACTUAL_WIDTH - 1, 0, SH110X_WHITE);
    drawPixelActual(0, ACTUAL_HEIGHT - 1, SH110X_WHITE);
    drawPixelActual(ACTUAL_WIDTH - 1, ACTUAL_HEIGHT - 1, SH110X_WHITE);

    // Show uptime
    setCursorActual(0, 30);
    display.print(F("Up:"));
    display.print(millis() / 1000);
    display.print(F("s"));

    display.display();
}

// Scrolling text test
void displayScrollText()
{
    static int16_t textX = ACTUAL_WIDTH;
    static unsigned long lastScroll = 0;

    if (millis() - lastScroll > 100)
    {
        lastScroll = millis();
        textX -= 2;
        if (textX < -60)
            textX = ACTUAL_WIDTH; // Reset when text goes off screen
    }

    display.clearDisplay();

    setCursorActual(textX, 15);
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.print(F("Scrolling Text!"));

    // Add a static header
    setCursorActual(0, 0);
    display.print(F("Scroll Test"));

    // Add moving indicator
    drawPixelActual((millis() / 100) % ACTUAL_WIDTH, 35, SH110X_WHITE);

    display.display();
}

// Animated bar graph
void displayBarGraph()
{
    display.clearDisplay();

    setCursorActual(0, 0);
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.print(F("Bar Graph"));

    // Draw 6 animated bars
    for (int i = 0; i < 6; i++)
    {
        int barHeight = (sin((millis() / 200.0) + i) + 1) * 15; // 0-30 height
        int barX = i * 12;
        fillRectActual(barX, ACTUAL_HEIGHT - barHeight, 8, barHeight, SH110X_WHITE);

        // Add value labels
        setCursorActual(barX, ACTUAL_HEIGHT - barHeight - 8);
        display.print(barHeight);
    }

    display.display();
}

// Circle and shape test
void displayCircleTest()
{
    display.clearDisplay();

    setCursorActual(0, 0);
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.print(F("Shapes"));

    // Animated expanding circle
    int radius = (millis() / 100) % 15 + 1;
    int centerX = ACTUAL_WIDTH / 2;
    int centerY = ACTUAL_HEIGHT / 2 + 5;

    // Draw circle using pixels (since circle function might not be available)
    for (int angle = 0; angle < 360; angle += 15)
    {
        int x = centerX + cos(angle * PI / 180) * radius;
        int y = centerY + sin(angle * PI / 180) * radius;
        if (x >= 0 && x < ACTUAL_WIDTH && y >= 0 && y < ACTUAL_HEIGHT)
        {
            drawPixelActual(x, y, SH110X_WHITE);
        }
    }

    // Add some triangles
    drawLineActual(5, 35, 15, 25, SH110X_WHITE);
    drawLineActual(15, 25, 25, 35, SH110X_WHITE);
    drawLineActual(25, 35, 5, 35, SH110X_WHITE);

    display.display();
}

// Moving line patterns
void displayLinePattern()
{
    display.clearDisplay();

    setCursorActual(0, 0);
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.print(F("Lines"));

    // Animated diagonal lines
    int offset = (millis() / 50) % 20;

    for (int i = -20; i < ACTUAL_WIDTH + 20; i += 10)
    {
        drawLineActual(i + offset, 10, i + offset + 20, 30, SH110X_WHITE);
    }

    // Vertical lines moving horizontally
    int vOffset = (millis() / 100) % ACTUAL_WIDTH;
    for (int i = 0; i < 3; i++)
    {
        int x = (vOffset + i * 20) % ACTUAL_WIDTH;
        drawLineActual(x, 10, x, ACTUAL_HEIGHT - 1, SH110X_WHITE);
    }

    display.display();
}

// Gradient-like effect using dithering
void displayGradientTest()
{
    display.clearDisplay();

    setCursorActual(0, 0);
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.print(F("Gradient"));

    // Create gradient effect using dithering
    for (int y = 10; y < ACTUAL_HEIGHT; y++)
    {
        for (int x = 0; x < ACTUAL_WIDTH; x++)
        {
            // Create a gradient from left to right
            int density = (x * 8) / ACTUAL_WIDTH; // 0-7 density levels

            // Dithering pattern
            bool shouldDraw = false;
            int pattern = (x % 4) + (y % 4) * 4; // 0-15 pattern index

            if (density == 0)
                shouldDraw = false;
            else if (density == 1)
                shouldDraw = (pattern == 0);
            else if (density == 2)
                shouldDraw = (pattern % 8 == 0);
            else if (density == 3)
                shouldDraw = (pattern % 4 == 0);
            else if (density == 4)
                shouldDraw = (pattern % 2 == 0);
            else if (density == 5)
                shouldDraw = (pattern % 4 != 1);
            else if (density == 6)
                shouldDraw = (pattern % 8 != 1);
            else if (density == 7)
                shouldDraw = (pattern != 15);

            if (shouldDraw)
            {
                drawPixelActual(x, y, SH110X_WHITE);
            }
        }
    }

    display.display();
}
