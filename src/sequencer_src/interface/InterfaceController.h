#ifndef InterfaceController_h
#define InterfaceController_h

#include <inttypes.h>

#include "../model/AppData.h"
#include "../sequencer/Sequencer.h"
#include "../sequencer/SequencerEventListener.h"
#include "InterfaceEvent.h"
#include "Keyboard.h"
#include "views/View.h"
#include "./views/SequenceView.h"
#include "./views/ParameterView.h"
#include "./views/SequenceMatrixView.h"
#include "./views/FileView.h"
#include "./views/HelpView.h"

class InterfaceController : public SequencerEventListener {

public:
    InterfaceController(AppData& _appData, Sequencer& _sequencer, Keyboard& _keyboard);
    void init();
    void render();
    void handleEvent(InterfaceEvent event);
    virtual void onTick();

private:
    AppData& appData;
    Sequencer& sequencer;
    Keyboard& keyboard;

    View* currentView;
    View* previousView;

    SequenceMatrixView sequenceMatrixView;
    SequenceView sequenceView;
    ParameterView parameterView;
    FileView fileView;
    HelpView helpView;

    bool recording;

    void switchToParameterView();
    void switchToSequenceView();

};

#endif
