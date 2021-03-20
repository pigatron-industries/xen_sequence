#include "Component.h"
#include "interface/views/Org_01.h"
#include "lib/util/debug.h"


void Component::render(bool full) { 
    DEBUG("Component::render")
    GraphicsContext g = GraphicsContext(full); 
    if(full) {
        Hardware::display.fillScreen(Colour::BLACK);
    }
    Hardware::display.setFont(Org_01);
    Hardware::display.setTextSize(1);
    render(g); 
}
