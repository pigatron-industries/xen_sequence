#include "LedMatrix.h"

#include <Arduino.h>

LedMatrix::LedMatrix(uint8_t _xPinCount, uint8_t _yPinCount, uint8_t* _xPins, uint8_t* _yPins):
    xPinCount(_xPinCount),
    yPinCount(_yPinCount),
    xPins(_xPins),
    yPins(_yPins) {
        yCurrent = 0;
        for(uint8_t i = 0; i < xPinCount; i++) {
            pinMode(xPins[i], OUTPUT);
        }
        for(uint8_t i = 0; i < yPinCount; i++) {
            pinMode(yPins[i], OUTPUT);
        }
        values = new bool[xPinCount*yPinCount];
        for(uint8_t i = 0; i < xPinCount*yPinCount; i++) {
            values[i] = false;
        }
}

void LedMatrix::setValueAt(uint8_t x, uint8_t y, bool value) {
    values[x + y*xPinCount] = value;
}

bool LedMatrix::getValueAt(uint8_t x, uint8_t y) {
    return values[x + y*xPinCount];
}

void LedMatrix::execute() {
    //turn off current row
    digitalWrite(yPins[yCurrent], LOW);

    //move to next row
    yCurrent++;
    if(yCurrent >= yPinCount) {
        yCurrent = 0;
    }

    //set x pins to correct values for current row
    for(uint8_t xCurrent = 0; xCurrent < xPinCount; xCurrent++) {
        digitalWrite(xPins[xCurrent], values[xCurrent + yCurrent*xPinCount]);
    }

    //turn on current row
    digitalWrite(yPins[yCurrent], HIGH);
}