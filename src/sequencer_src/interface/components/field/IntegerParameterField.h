#ifndef IntegerParameterField_h
#define IntegerParameterField_h

#include "ParameterField.h"

class IntegerParameterField : public ParameterField {

public:
    IntegerParameterField(const char* _name, int16_t _min, int16_t _max, const char* _unit = "");
    void increment(int16_t amount);
    void decrement(int16_t amount);
    virtual void render(GraphicsContext& graphicsContext);

    void setValue(int16_t _value) { value = _value; dirtyValue = true; }
    uint16_t getValue() { return value; }

private:
    int16_t value;
    int16_t min;
    int16_t max;
    const char* unit;

};


#endif
