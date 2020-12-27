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

    TextComponent titleComponent;
    //Component* selectedComponent;
    ListComponent listComponent;
    TextComponent newFileComponent;
    TextComponent fileComponents[MAX_FILES];

    bool saveConfirmation;
    bool loadConfirmation;

    void listFiles();

    void save();
    void load();

    bool confirmLoad();
    bool confirmSave();
    void cancelDialog();

    void navigate();

};

#endif
