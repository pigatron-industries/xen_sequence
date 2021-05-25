#include "HelpView.h"
#include "interface/Hardware.h"

HelpView::HelpView() {
}

void HelpView::init() {
}

void HelpView::render(GraphicsContext& g) {
    Hardware::display.setCursor(0, 12);
    Hardware::display.setTextColour(Colour(0, 0, 255));
    Hardware::display.println("LEFT SIDE");
    Hardware::display.println();

    Hardware::display.setTextColour(Colour(255, 255, 255));
    Hardware::display.println("RCRD PLAY PREV NEXT");
    Hardware::display.println();
    Hardware::display.println("VIEW SLCT FILE HELP");
    Hardware::display.println("X    X    X    X");
    Hardware::display.println();
    Hardware::display.println();

    Hardware::display.setTextColour(Colour(0, 0, 255));
    Hardware::display.println("RIGHT SIDE");
    Hardware::display.println();

    Hardware::display.setTextColour(Colour(255, 255, 255));
    Hardware::display.println("STRT END  X    X");
    Hardware::display.println();
    Hardware::display.println("ADD  DEL  X    X");
    Hardware::display.println("MOVE COPY PSTE X");

    Hardware::display.updateScreen();
}

void HelpView::handleEvent(InterfaceEvent event) {
    switch(event.eventType) {
        case InterfaceEventType::KEY_RECORD:
        case InterfaceEventType::KEY_PLAY_STOP:
            renderPage(event.eventType);
            break;
        default:
            break;
    }
}

void HelpView::renderPage(InterfaceEventType eventType) {
    Hardware::display.fillScreen(Colour::BLACK);
    Hardware::display.setTextColour(Colour::WHITE);
    Hardware::display.setCursor(0, 12);

    switch(eventType) {
        case InterfaceEventType::KEY_RECORD:
            Hardware::display.println("RECORD");
            break;
        case InterfaceEventType::KEY_PLAY_STOP:
            Hardware::display.println("PLAY / STOP");
            Hardware::display.println();
            Hardware::display.setTextColour(Colour::GREEN);
            Hardware::display.println("GREEN   - PLAY SONG");
            Hardware::display.setTextColour(Colour::YELLOW);
            Hardware::display.println("YELLOW  - LOOP SONG");
            Hardware::display.setTextColour(Colour::PURPLE);
            Hardware::display.println("MAGENTA - LOOP BAR");
            Hardware::display.setTextColour(Colour::CYAN);
            Hardware::display.println("CYAN    - LOOP SELECTION");
            break;
        default:
            break;
    }
}