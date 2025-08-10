#include "display_tests.h"

// Scrolling text test
void displayScrollText()
{
    static int16_t textX = ACTUAL_WIDTH;
    static unsigned long lastScroll = 0;

    if (millis() - lastScroll > 67) // Increased speed by 50% (was 100ms)
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
