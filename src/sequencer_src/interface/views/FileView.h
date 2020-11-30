#ifndef FileView_h
#define FileView_h

#include <inttypes.h>

#include "View.h"
#include "../../repository/DataRepository.h"


class FileView : public View {

public:
    FileView();
    void load();
    virtual void render(GraphicsContext& g);
    virtual void handleEvent(InterfaceEvent event);

private:
    String currentDirectory = String("/");

};

#endif
