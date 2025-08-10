#include "display_tests.h"

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
