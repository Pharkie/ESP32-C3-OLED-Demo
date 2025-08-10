#include "display_tests.h"

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
