#include "display_tests.h"

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
