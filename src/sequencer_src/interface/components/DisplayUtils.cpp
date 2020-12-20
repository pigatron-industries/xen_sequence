#include "DisplayUtils.h"

#include "../Hardware.h"

#define TEXT_HEIGHT 7

void DisplayUtils::drawDialog(const char *str, int16_t w, int16_t h) {
    int16_t x = (DISPLAY_WIDTH * 0.5) - (w * 0.5);
    int16_t y = (DISPLAY_HEIGHT * 0.5) - (h * 0.5);
    Hardware::display.fillRect(x, y, w, h, Colour::BLACK);
    Hardware::display.drawRect(x, y, w, h, Colour::ORANGE);
    Hardware::display.setTextColour(Colour::ORANGE);
    Hardware::display.setCursor(x + 5, y+h - ((h-TEXT_HEIGHT)*0.5) - 1);
    Hardware::display.print(str);
}
