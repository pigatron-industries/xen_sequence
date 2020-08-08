#include "SPISlave.h"

uint8_t SPISlave::mosiPin;
uint8_t SPISlave::sckPin;
uint8_t SPISlave::pos;
uint8_t SPISlave::dataByte;
event_cb_t SPISlave::callback;


void SPISlave::begin(uint8_t _mosiPin, uint8_t _sckPin, event_cb_t _callback) {
    mosiPin = _mosiPin;
    sckPin = _sckPin;
    callback = _callback;
    pinMode(mosiPin, INPUT);
    pinMode(sckPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(sckPin), process, RISING);
    pos = 0;
    dataByte = 0;
}

void SPISlave::end() {
    detachInterrupt(digitalPinToInterrupt(sckPin));
}

void SPISlave::process() {
    dataByte |= digitalRead(mosiPin) << pos;
    if(pos == 7) {
        callback(dataByte);
        pos = 0;
        dataByte = 0;
    } else {
        pos++;
    }
}
