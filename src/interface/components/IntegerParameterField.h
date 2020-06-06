#ifndef IntegerParameterField_h
#define IntegerParameterField_h

#include "ParameterField.h"

class IntegerParameterField : public ParameterField {

public:
    IntegerParameterField(const char* _name, uint16_t _value, uint16_t _min, uint16_t _max, const char* _unit = "");
    void increment();
    void decrement();
    void render(Display& display, uint8_t row, bool selected);

private:
    uint16_t value;
    uint16_t min;
    uint16_t max;
    const char* unit;

};


#endif
