#include "display_tests.h"

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
