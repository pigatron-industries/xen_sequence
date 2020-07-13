#ifndef LedMatrix_h
#define LedMatrix_h

#include <inttypes.h>

#define X_PIN_COUNT 12
#define Y_PIN_COUNT 6

class LedMatrix {
    public:
        LedMatrix(uint8_t _xPinCount, uint8_t _yPinCount, uint8_t* _xPins, uint8_t* _yPins);
        void setValueAt(uint8_t x, uint8_t y, bool value);
        bool getValueAt(uint8_t x, uint8_t y);

        void execute();

    private:
        uint8_t xPinCount;
        uint8_t yPinCount;
        uint8_t* xPins;
        uint8_t* yPins;
        bool* values;

        uint8_t yCurrent;
};

#endif
