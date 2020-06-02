#ifndef Display_h
#define Display_h

#include <inttypes.h>
#include <Arduino.h>
#include <gfxfont.h>

// Text alignments
static const uint8_t ALIGN_LEFT = 0;
static const uint8_t ALIGN_CENTER = 1;
static const uint8_t ALIGN_RIGHT = 2;

struct Colour {
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	Colour() {}
	Colour(int16_t _r, int16_t _g, int16_t _b) : r(_r), g(_g), b(_b) {}
};


class Display : public Print {

public:
    Display();
    void init();
    void updateScreen();
    void fillScreen(const Colour &colour);

    // shapes
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, const Colour &colour);
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, const Colour &colour);
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, const Colour &colour);
    void drawCircle(int16_t x0, int16_t y0, int16_t r, const Colour &colour);
    void fillCircle(int16_t x0, int16_t y0, int16_t r, const Colour &colour);
    void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, const Colour &colour);
    void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, const Colour &colour);
    void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, const Colour &colour);
    void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, const Colour &colour);
    void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, const Colour &colour);

    // text
    void setCursor(int16_t x, int16_t y);
    int16_t getCursorX() const;
    int16_t getCursorY() const;
    void setTextColour(Colour colour);
    void setTextColour(const Colour &foreground, const Colour &background);
    void setTextSize(uint8_t new_size);
    void setTextWrap(bool _wrap);
    void cp437(bool use_cp437 = true);
    void setFont(const GFXfont &new_font);
    void drawText(const char *str, int16_t x, int16_t y, uint8_t align=ALIGN_LEFT);
    uint16_t getTextWidth(const char *str);
    size_t write(uint8_t c);
    void drawChar(int16_t x, int16_t y, unsigned char c, Colour color, Colour bg, uint8_t size);

private:

};

#endif
