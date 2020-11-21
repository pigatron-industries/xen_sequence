#ifndef InterfaceController_h
#define InterfaceController_h

#include <inttypes.h>

#include "../model/AppData.h"
#include "../sequencer/Sequencer.h"
#include "../sequencer/SequencerEventListener.h"
#include "InterfaceEvent.h"
#include "Keyboard.h"
#include "View.h"
#include "./views/SequenceView.h"
#include "./views/ParameterView.h"
#include "./views/SequenceMatrixView.h"

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

    SequenceMatrixView sequenceMatrixView;
    SequenceView sequenceView;
    ParameterView parameterView;

    bool recording;

    void switchToParameterView();
    void switchToSequenceView();

};

#endif
