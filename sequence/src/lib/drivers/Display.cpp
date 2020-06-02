#include "Display.h"

#include <ssd1351.h>

ssd1351::SSD1351<ssd1351::HighColor, ssd1351::SingleBuffer, 128, 128> oled;

ssd1351::HighColor c(const Colour &colour) {
    return ssd1351::HighColor(colour.r, colour.g, colour.b);
}

Display::Display() {
}

void Display::init() {
    oled.begin();
}

void Display::updateScreen() {
    oled.updateScreen();
}

void Display::fillScreen(const Colour &colour) {
    oled.fillScreen(c(colour));
}

// shapes
void Display::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, const Colour &colour) {
    oled.drawLine(x0, y0, x1, y1, c(colour));
}

void Display::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, const Colour &colour) {
    oled.drawRect(x, y, w, h, c(colour));
}

void Display::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, const Colour &colour) {
    oled.fillRect(x, y, w, h, c(colour));
}

// void drawCircle(int16_t x0, int16_t y0, int16_t r, const Colour &colour);
// void fillCircle(int16_t x0, int16_t y0, int16_t r, const Colour &colour);
// void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, const Colour &colour);
// void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, const Colour &colour);
// void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, const Colour &colour);
// void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, const Colour &colour);
// void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, const Colour &colour);
//
// // text
void Display::setCursor(int16_t x, int16_t y) {
    oled.setCursor(x, y);
}
// int16_t getCursorX() const;
// int16_t getCursorY() const;
void Display::setTextColour(Colour colour) {
    oled.setTextColor(c(colour));
}

void Display::setTextColour(const Colour &foreground, const Colour &background) {
    oled.setTextColor(c(foreground), c(background));
}

void Display::setTextSize(uint8_t new_size) {
    oled.setTextSize(new_size);
}

// void setTextWrap(bool _wrap);
// void cp437(bool use_cp437 = true);

void Display::setFont(const GFXfont &new_font) {
    oled.setFont(new_font);
}

void Display::drawText(const char *str, int16_t x, int16_t y, uint8_t align=ALIGN_LEFT) {
    oled.drawText(str, x, y, align);
}
// uint16_t getTextWidth(const char *str);

size_t Display::write(uint8_t c) {
    return oled.write(c);
}

// void drawChar(int16_t x, int16_t y, unsigned char c, Colour color, Colour bg, uint8_t size);
