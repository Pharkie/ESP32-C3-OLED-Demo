#include "display_tests.h"

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
