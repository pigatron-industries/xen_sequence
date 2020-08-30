#ifndef KeyboardLedMatrix_h
#define KeyboardLedMatrix_h

#include <inttypes.h>
#include <SoftwareSerial.h>

#define X_LED_SIZE 12
#define Y_LED_SIZE 6

class KeyboardLedMatrix {

public:
    KeyboardLedMatrix();

    void setLedValueAt(uint8_t x, uint8_t y, bool value);

private:
    bool values[X_LED_SIZE*Y_LED_SIZE];

};

#endif
