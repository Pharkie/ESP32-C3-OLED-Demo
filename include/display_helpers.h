#ifndef DISPLAY_HELPERS_H
#define DISPLAY_HELPERS_H

#include "config.h"

// Helper functions for abstracted display positioning
void setCursorActual(int16_t x, int16_t y);
void drawPixelActual(int16_t x, int16_t y, uint16_t color);
void drawLineActual(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
void drawRectActual(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void fillRectActual(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

#endif // DISPLAY_HELPERS_H
