#ifndef Component_h
#define Component_h

#include <inttypes.h>
#include "interface/graphics/GraphicsContext.h"
#include "interface/Hardware.h"

class Component : public Focusable {

public:
    Component() {}
    virtual void render(GraphicsContext& graphicsContext);
    void render(bool full = true);

    int16_t getTop() { return top; }
    uint16_t getHeight() { return height; }
    uint16_t getWidth() { return width; }
    bool getVisibility() { return visible; }
    bool getFocusable() { return focusable; }

    void setTop(int16_t top) { this->top = top; }
    void setHeight(uint16_t height) { this->height = height; }
    void setWidth(uint16_t width) { this->width = width; }
    void setVisibility(bool visible) { this->visible = visible; }
    void setFocusable(bool focusable) { this->focusable = focusable; }

protected:
    int16_t top;
    uint16_t height;
    uint16_t width;
    bool visible = true;
    bool focusable = false;
    bool rerenderFull = false;

};


#endif
