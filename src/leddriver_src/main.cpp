#include <Arduino.h>
#include "SPI.h"

#include "LedMatrix.h"

#define X_PIN_COUNT 12
#define Y_PIN_COUNT 6

uint8_t xPins[X_PIN_COUNT] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12};
uint8_t yPins[Y_PIN_COUNT] = {A0, A1, A2, A3, A4, A5};
LedMatrix ledMatrix = LedMatrix(X_PIN_COUNT, Y_PIN_COUNT, xPins, yPins);

#define COMMAND_OFF 0xF0
#define COMMAND_ON 0xFF

uint8_t bufferPos = 0;
uint8_t buffer[3];

void receiveData() {
    uint8_t b = SPI.transfer(0);
    if (b == COMMAND_OFF || b == COMMAND_ON) {
        buffer[0] = b;
        bufferPos = 1;
    } else if(bufferPos < 3) {
        buffer[bufferPos] = b;
        bufferPos++;
        if(bufferPos == 3) {
            ledMatrix.setValueAt(buffer[1], buffer[2], buffer[0] == COMMAND_ON ? HIGH : LOW);
        }
    }
}

void setup() {
    SPI.begin(SPI_SLAVE);
    SPI.attachInterrupt(receiveData);
}

boolean runTest = true;
uint16_t time = 0;
uint8_t rgb = 0;

void runTestLoop() {
    time++;
    if(time == 250) {
        rgb++;
        ledMatrix.setValueAt(0, 0, (rgb >> 0) & 0x01); // Red
        ledMatrix.setValueAt(1, 0, (rgb >> 1) & 0x01); // Green
        ledMatrix.setValueAt(2, 0, (rgb >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(0, 1, (rgb >> 1) & 0x01); // Red
        ledMatrix.setValueAt(1, 1, (rgb >> 2) & 0x01); // Green
        ledMatrix.setValueAt(2, 1, (rgb >> 0) & 0x01); // Blue
        time = 0;
        if(rgb == 8) {
            runTest = false;
        }
    }
}

void loop() {
    ledMatrix.execute();
    if(runTest) {
        runTestLoop();
    }
    delay(1);
}