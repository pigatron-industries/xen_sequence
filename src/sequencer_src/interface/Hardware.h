#ifndef Hardware_h
#define Hardware_h

#include <inttypes.h>

#include "../lib/drivers/Display.h"
#include "../lib/drivers/LedMatrix.h"


class Hardware {

public:
    static void init();
    static Display display;
    static LedMatrix ledMatrix;

private:
    Hardware() {}
    
};

#endif
