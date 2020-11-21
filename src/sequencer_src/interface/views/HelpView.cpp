#include "HelpView.h"
#include "../Hardware.h"

HelpView::HelpView() {
}

void HelpView::render(bool full = false) {
    Hardware::display.fillScreen(Colour(0, 0, 0));
}

void HelpView::handleEvent(InterfaceEvent event) {

}
