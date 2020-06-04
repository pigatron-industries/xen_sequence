#include "Matrix.h"

#include "../../hwconfig.h"

#define BRIGHTNESS 1

Matrix::Matrix() {
}

void Matrix::init() {
    FastLED.addLeds<APA102, MATRIX_DATA_PIN, MATRIX_CLOCK_PIN, BGR>(leds, MATRIX_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    for(int i = 0; i < MATRIX_LEDS; i++) {
        leds[i] = CRGB::Black;
    }
    FastLED.show();
}

void Matrix::update() {
    FastLED.show();
}

void Matrix::setPixel(uint8_t x, uint8_t y, CRGB colour) {
    uint8_t led = xyToLedNum(x, y);
    if(led >= 0 && led < MATRIX_LEDS) {
        leds[led] = colour;
    }
}

CRGB Matrix::getPixel(uint8_t x, uint8_t y) {
    uint8_t led = xyToLedNum(x, y);
    if(led >= 0 && led < MATRIX_LEDS) {
        return leds[led];
    } else {
        return CRGB::Black;
    }
}

uint8_t Matrix::xyToLedNum(uint8_t x, uint8_t y) {
    return (MATRIX_LEDS-1) - ((y * MATRIX_ROWS) + x);
}

void Matrix::test() {
    setPixel(7, 7, CRGB::Red);
    update();
}
