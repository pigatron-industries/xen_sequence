#include "AbstractParameterView.h"

void AbstractParameterView::init() {

}

void AbstractParameterView::render(GraphicsContext& g) {
    fields.render(g);
}

InterfaceEvent AbstractParameterView::handleEvent(InterfaceEvent event) {

}
