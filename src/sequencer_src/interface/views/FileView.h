#ifndef FileView_h
#define FileView_h

#include <inttypes.h>

#include "View.h"
#include "../components/ListComponent.h"
#include "../components/TextComponent.h"
#include "../../repository/DataRepository.h"


class FileView : public View {

public:
    static const int MAX_FILES = 255;

    FileView();
    void load();
    virtual void render(GraphicsContext& g);
    virtual void handleEvent(InterfaceEvent event);

private:
    String currentDirectory = String("/");
    int selectedIndex;
    int listSize;

    Component* selectedComponent;
    ListComponent listComponent;
    TextComponent textComponents[MAX_FILES];

};

#endif
