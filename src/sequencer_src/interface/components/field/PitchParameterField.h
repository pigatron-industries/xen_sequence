#ifndef PitchParameterField_h
#define PitchParameterField_h

#include "ParameterField.h"

class PitchParameterField : public ParameterField {

public:
    PitchParameterField(const char* _name);
    void increment(int16_t amount);
    void decrement(int16_t amount);
    virtual void render(GraphicsContext& graphicsContext);

    void setValue(int16_t _value) { value = _value; dirtyValue = true; }
    uint16_t getValue() { return value; }

private:
    int16_t value;
    int16_t min = 0;
    int16_t max = 127;

    char const* noteNames[128] = {
        "C -1", "C#-1", "D -1", "D#-1", "E -1", "F -1", "F#-1", "G -1", "G#-1", "A -1", "A#-1", "B -1",
        "C  0", "C# 0", "D  0", "D# 0", "E  0", "F  0", "F# 0", "G  0", "G# 0", "A  0", "A# 0", "B  0",
        "C  1", "C# 1", "D  1", "D# 1", "E  1", "F  1", "F# 1", "G  1", "G# 1", "A  1", "A# 1", "B  1",
        "C  2", "C# 2", "D  2", "D# 2", "E  2", "F  2", "F# 2", "G  2", "G# 2", "A  2", "A# 2", "B  2",
        "C  3", "C# 3", "D  3", "D# 3", "E  3", "F  3", "F# 3", "G  3", "G# 3", "A  3", "A# 3", "B  3",
        "C  4", "C# 4", "D  4", "D# 4", "E  4", "F  4", "F# 4", "G  4", "G# 4", "A  4", "A# 4", "B  4",
        "C  5", "C# 5", "D  5", "D# 5", "E  5", "F  5", "F# 5", "G  5", "G# 5", "A  5", "A# 5", "B  5",
        "C  6", "C# 6", "D  6", "D# 6", "E  6", "F  6", "F# 6", "G  6", "G# 6", "A  6", "A# 6", "B  6",
        "C  7", "C# 7", "D  7", "D# 7", "E  7", "F  7", "F# 7", "G  7", "G# 7", "A  7", "A# 7", "B  7",
        "C  8", "C# 8", "D  8", "D# 8", "E  8", "F  8", "F# 8", "G  8", "G# 8", "A  8", "A# 8", "B  8",
        "C  9", "C# 9", "D  9", "D# 9", "E  9", "F  9", "F# 9", "G  9"
    };

};


#endif
