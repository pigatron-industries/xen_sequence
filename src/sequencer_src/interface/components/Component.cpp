#include "Component.h"
#include "../Hardware.h"
#include "../views/Org_01.h"


void Component::render(bool full) { 
    GraphicsContext g = GraphicsContext(full); 
    if(full) {
        Hardware::display.fillScreen(Colour::BLACK);
    }
    Hardware::display.setFont(Org_01);
    Hardware::display.setTextSize(1);
    render(g); 
}
