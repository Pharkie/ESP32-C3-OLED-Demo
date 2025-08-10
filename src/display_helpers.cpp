#include "display_helpers.h"

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
