#ifndef Time_h
#define Time_h

#include <Arduino.h>

class Time {

public:
    Time() {}
    void init();
    char* getDateTime();

private:
    char datetime[20];
    
};

#endif
