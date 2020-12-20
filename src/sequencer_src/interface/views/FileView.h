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
    void init();
    virtual void render(GraphicsContext& g);
    virtual InterfaceEvent handleEvent(InterfaceEvent event);

private:
    String currentDirectory = String("/");
    int selectedIndex;
    int listSize;

    TextComponent titleComponent;
    Component* selectedComponent;
    ListComponent listComponent;
    TextComponent textComponents[MAX_FILES];

    void save();
    void load();

    bool confirmLoad();
    bool confirmSave();
    void cancelDialog();

    bool saveConfirmation;
    bool loadConfirmation;

};

#endif
