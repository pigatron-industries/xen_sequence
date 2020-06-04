#ifndef Matrix_h
#define Matrix_h

#include <FastLED.h>

#define MATRIX_ROWS 8
#define MATRIX_COLS 16
#define MATRIX_LEDS MATRIX_ROWS * MATRIX_COLS

class Matrix {

public:
    Matrix();
    void init();
    void setPixel(uint8_t x, uint8_t y, CRGB colour);
    void update();

    void test();

private:
    CRGB leds[MATRIX_LEDS];

    uint8_t xyToLedNum(uint8_t x, uint8_t y);

};

#endif
