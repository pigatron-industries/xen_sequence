#include "HelpView.h"
#include "interface/Hardware.h"

HelpView::HelpView() {
}

void HelpView::render(GraphicsContext& g) {
    Hardware::display.setCursor(0, 12);
    Hardware::display.setTextColour(Colour(0, 0, 255));
    Hardware::display.println("LEFT SIDE");
    Hardware::display.println();

    Hardware::display.setTextColour(Colour(255, 255, 255));
    Hardware::display.println("RCRD PLAY PREV NEXT");
    Hardware::display.println();
    Hardware::display.println("VIEW SLCT X    X");
    Hardware::display.println("X    X    X    X");
    Hardware::display.println();
    Hardware::display.println();

    Hardware::display.setTextColour(Colour(0, 0, 255));
    Hardware::display.println("RIGHT SIDE");
    Hardware::display.println();

    Hardware::display.setTextColour(Colour(255, 255, 255));
    Hardware::display.println("LOOP X    X    X");
    Hardware::display.println();
    Hardware::display.println("EVNT COPY PSTE X");
    Hardware::display.println("X    X    X    HELP");

    Hardware::display.updateScreen();
}

InterfaceEvent HelpView::handleEvent(InterfaceEvent event) {
    switch(event.eventType) {
        case InterfaceEventType::KEY_RECORD:
        case InterfaceEventType::KEY_PLAY_STOP:
        case InterfaceEventType::KEY_LOOP:
            renderPage(event.eventType);
            break;
        default:
            break;
    }

    return InterfaceEvent::NONE;
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
            break;
        case InterfaceEventType::KEY_LOOP:
            Hardware::display.println("PLAYBACK/RECORD MODE");
            Hardware::display.println();
            Hardware::display.setTextColour(Colour::GREEN);
            Hardware::display.println("GREEN  - PLAY SONG");
            Hardware::display.setTextColour(Colour::YELLOW);
            Hardware::display.println("YELLOW - LOOP SONG");
            Hardware::display.setTextColour(Colour::RED);
            Hardware::display.println("RED    - LOOP BAR");
            Hardware::display.setTextColour(Colour::PURPLE);
            Hardware::display.println("PURPLE - PAUSED");
            Hardware::display.setTextColour(Colour::BLUE);
            Hardware::display.println("BLUE   - ON MIDI");
            break;
        default:
            break;
    }
}