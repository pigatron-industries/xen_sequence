#ifndef EnumParameterField_h
#define EnumParameterField_h

#include "ParameterField.h"

class EnumParameterField : public ParameterField {

public:
    EnumParameterField(const char* _name, const char** names, int8_t size);
    void increment(int16_t amount);
    void decrement(int16_t amount);
    virtual void render(GraphicsContext& graphicsContext);

    void setValue(int8_t _value) { value = _value; dirtyValue = true; }
    uint8_t getValue() { return value; }
    const char* getName() { return names[value]; }

private:
    int8_t value;
    int8_t size;
    const char** names;

};


#endif
