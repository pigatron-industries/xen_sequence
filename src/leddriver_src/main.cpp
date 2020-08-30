#include <Arduino.h>
#include <SoftwareSerial.h>

#include "LedMatrix.h"

#define MOSI_PIN 11
#define SCK_PIN 13

#define X_PIN_COUNT 12
#define Y_PIN_COUNT 6

uint8_t xPins[X_PIN_COUNT] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
uint8_t yPins[Y_PIN_COUNT] = {A0, A1, A2, A3, A4, A5};
LedMatrix ledMatrix = LedMatrix(X_PIN_COUNT, Y_PIN_COUNT, xPins, yPins);

#define COMMAND_OFF 0xF0
#define COMMAND_ON 0xFF

uint8_t bufferPos = 0;
uint8_t buffer[3];

boolean runTest = true;
uint16_t time = 0;
uint8_t rgb = 0;

void blank() {
    for(uint8_t x = 0; x < X_PIN_COUNT; x++) {
        for(uint8_t y = 0; y < Y_PIN_COUNT; y++) {
            ledMatrix.setValueAt(x, y, 0);
        }
    }
}

void receiveData() {
    uint8_t b = Serial.read();

    // ledMatrix.setValueAt(0, 0, (b >> 0) & 0x01);
    // ledMatrix.setValueAt(3, 0, (b >> 1) & 0x01);
    // ledMatrix.setValueAt(6, 0, (b >> 2) & 0x01);
    // ledMatrix.setValueAt(9, 0, (b >> 3) & 0x01);
    // ledMatrix.setValueAt(0, 1, (b >> 4) & 0x01);
    // ledMatrix.setValueAt(3, 1, (b >> 5) & 0x01);
    // ledMatrix.setValueAt(6, 1, (b >> 6) & 0x01);
    // ledMatrix.setValueAt(9, 1, (b >> 7) & 0x01);

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
    Serial.begin(9600);
}

void runTestLoop() {
    time++;
    if(time == 100) {
        rgb++;

        ledMatrix.setValueAt(0, 0, (rgb >> 0) & 0x01); // Red
        ledMatrix.setValueAt(1, 0, (rgb >> 1) & 0x01); // Green
        ledMatrix.setValueAt(2, 0, (rgb >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(3, 0, (rgb+1 >> 0) & 0x01); // Red
        ledMatrix.setValueAt(4, 0, (rgb+1 >> 1) & 0x01); // Green
        ledMatrix.setValueAt(5, 0, (rgb+1 >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(6, 0, (rgb+2 >> 0) & 0x01); // Red
        ledMatrix.setValueAt(7, 0, (rgb+2 >> 1) & 0x01); // Green
        ledMatrix.setValueAt(8, 0, (rgb+2 >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(9, 0, (rgb+3 >> 0) & 0x01); // Red
        ledMatrix.setValueAt(10, 0, (rgb+3 >> 1) & 0x01); // Green
        ledMatrix.setValueAt(11, 0, (rgb+3 >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(0, 1, (rgb+3 >> 0) & 0x01); // Red
        ledMatrix.setValueAt(1, 1, (rgb+3 >> 1) & 0x01); // Green
        ledMatrix.setValueAt(2, 1, (rgb+3 >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(3, 1, (rgb+2 >> 0) & 0x01); // Red
        ledMatrix.setValueAt(4, 1, (rgb+2 >> 1) & 0x01); // Green
        ledMatrix.setValueAt(5, 1, (rgb+2 >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(6, 1, (rgb+1 >> 0) & 0x01); // Red
        ledMatrix.setValueAt(7, 1, (rgb+1 >> 1) & 0x01); // Green
        ledMatrix.setValueAt(8, 1, (rgb+1 >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(9, 1, (rgb >> 0) & 0x01); // Red
        ledMatrix.setValueAt(10, 1, (rgb >> 1) & 0x01); // Green
        ledMatrix.setValueAt(11, 1, (rgb >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(0, 2, (rgb >> 0) & 0x01); // Red
        ledMatrix.setValueAt(1, 2, (rgb >> 1) & 0x01); // Green
        ledMatrix.setValueAt(2, 2, (rgb >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(3, 2, (rgb+1 >> 0) & 0x01); // Red
        ledMatrix.setValueAt(4, 2, (rgb+1 >> 1) & 0x01); // Green
        ledMatrix.setValueAt(5, 2, (rgb+1 >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(6, 2, (rgb+2 >> 0) & 0x01); // Red
        ledMatrix.setValueAt(7, 2, (rgb+2 >> 1) & 0x01); // Green
        ledMatrix.setValueAt(8, 2, (rgb+2 >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(9, 2, (rgb+3 >> 0) & 0x01); // Red
        ledMatrix.setValueAt(10, 2, (rgb+3 >> 1) & 0x01); // Green
        ledMatrix.setValueAt(11, 2, (rgb+3 >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(0, 3, (rgb+3 >> 0) & 0x01); // Red
        ledMatrix.setValueAt(1, 3, (rgb+3 >> 1) & 0x01); // Green
        ledMatrix.setValueAt(2, 3, (rgb+3 >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(3, 3, (rgb+2 >> 0) & 0x01); // Red
        ledMatrix.setValueAt(4, 3, (rgb+2 >> 1) & 0x01); // Green
        ledMatrix.setValueAt(5, 3, (rgb+2 >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(6, 3, (rgb+1 >> 0) & 0x01); // Red
        ledMatrix.setValueAt(7, 3, (rgb+1 >> 1) & 0x01); // Green
        ledMatrix.setValueAt(8, 3, (rgb+1 >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(9, 3, (rgb >> 0) & 0x01); // Red
        ledMatrix.setValueAt(10, 3, (rgb >> 1) & 0x01); // Green
        ledMatrix.setValueAt(11, 3, (rgb >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(0, 4, (rgb >> 0) & 0x01); // Red
        ledMatrix.setValueAt(1, 4, (rgb >> 1) & 0x01); // Green
        ledMatrix.setValueAt(2, 4, (rgb >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(3, 4, (rgb+1 >> 0) & 0x01); // Red
        ledMatrix.setValueAt(4, 4, (rgb+1 >> 1) & 0x01); // Green
        ledMatrix.setValueAt(5, 4, (rgb+1 >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(6, 4, (rgb+2 >> 0) & 0x01); // Red
        ledMatrix.setValueAt(7, 4, (rgb+2 >> 1) & 0x01); // Green
        ledMatrix.setValueAt(8, 4, (rgb+2 >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(9, 4, (rgb+3 >> 0) & 0x01); // Red
        ledMatrix.setValueAt(10, 4, (rgb+3 >> 1) & 0x01); // Green
        ledMatrix.setValueAt(11, 4, (rgb+3 >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(0, 5, (rgb+3 >> 0) & 0x01); // Red
        ledMatrix.setValueAt(1, 5, (rgb+3 >> 1) & 0x01); // Green
        ledMatrix.setValueAt(2, 5, (rgb+3 >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(3, 5, (rgb+2 >> 0) & 0x01); // Red
        ledMatrix.setValueAt(4, 5, (rgb+2 >> 1) & 0x01); // Green
        ledMatrix.setValueAt(5, 5, (rgb+2 >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(6, 5, (rgb+1 >> 0) & 0x01); // Red
        ledMatrix.setValueAt(7, 5, (rgb+1 >> 1) & 0x01); // Green
        ledMatrix.setValueAt(8, 5, (rgb+1 >> 2) & 0x01); // Blue

        ledMatrix.setValueAt(9, 5, (rgb >> 0) & 0x01); // Red
        ledMatrix.setValueAt(10, 5, (rgb >> 1) & 0x01); // Green
        ledMatrix.setValueAt(11, 5, (rgb >> 2) & 0x01); // Blue

        time = 0;
        if(rgb == 8) {
            rgb = 0;
        }
    }
}

void loop() {
    ledMatrix.execute();

    if(runTest && Serial.available()) {
        runTest = false;
        blank();
    }

    if(Serial.available()) {
        receiveData();
    }

    if(runTest) {
        runTestLoop();
    }
    delay(1);
}