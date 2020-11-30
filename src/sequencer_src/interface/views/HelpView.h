#ifndef HelpView_h
#define HelpView_h

#include <inttypes.h>

#include "../View.h"


class HelpView : public View {

public:
    HelpView();
    virtual void render(GraphicsContext& g);
    virtual void handleEvent(InterfaceEvent event);

private:
    void renderPage(InterfaceEventType eventType);
};

#endif
