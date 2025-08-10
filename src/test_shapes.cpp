#include "display_tests.h"

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
