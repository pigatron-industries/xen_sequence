#ifndef GraphicsContext_h
#define GraphicsContext_h

#include <inttypes.h>

class GraphicsContext {

public:
    GraphicsContext() {}
    GraphicsContext(bool full) { this->full = full; }

    int xPos = 0;
    int yPos = 0;
    bool full = false;

};


#endif
