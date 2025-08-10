#include "display_tests.h"

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
