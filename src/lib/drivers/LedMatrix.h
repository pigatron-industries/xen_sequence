#ifndef LedMatrix_h
#define LedMatrix_h

#include <FastLED.h>

#define MATRIX_ROWS 8
#define MATRIX_COLS 16
#define MATRIX_LEDS MATRIX_ROWS * MATRIX_COLS

class LedMatrix {

public:
    LedMatrix();
    void init();
    void setPixel(uint8_t x, uint8_t y, CRGB colour);
    CRGB getPixel(uint8_t x, uint8_t y);
    void update();

    void test();

private:
    CRGB leds[MATRIX_LEDS];

    uint8_t xyToLedNum(uint8_t x, uint8_t y);

};

#endif
