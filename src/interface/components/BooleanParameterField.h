#ifndef BooleanParameterField_h
#define BooleanParameterField_h

#include "ParameterField.h"

class BooleanParameterField : public ParameterField {

public:
    BooleanParameterField(const char* _name);
    void increment();
    void decrement();
    void render(Display& display, uint8_t row, bool selected);

private:
    bool value;

};


#endif
