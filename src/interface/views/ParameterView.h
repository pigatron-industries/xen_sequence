#ifndef ParameterView_h
#define ParameterView_h

#include <inttypes.h>

#include "../View.h"
#include "SequenceMatrixView.h"
#include "../../model/AppData.h"
#include "../../lib/drivers/display.h"
#include "../components/ParameterField.h"

enum ParameterViewMode {
    PARAM_MODE_BAR, // Track length
    PARAM_MODE_CHANNEL, // Edit entire channel: Mute, length
    PARAM_MODE_EVENT //Edit note parameters
};

enum Parameter {
    PARAM_SELECT,
    PARAM_BAR_LENGTH,
    PARAM_BAR_BPM,
    PARAM_CHANNEL_MUTE,
    PARAM_EVENT_PITCH,
    PARAM_EVENT_GATE,
    PARAM_EVENT_DELAY,
    PARAM_EVENT_RATCHET,
};


class ParameterView : public View {

public:
    ParameterView(AppData& _appData, Display& _display, SequenceMatrixView& _sequenceMatrixView);
    virtual void render();
    virtual void handleEvent(Event event);

    void setBar(uint16_t _bar);

private:
    AppData& appData;
    Display& display;
    SequenceMatrixView& sequenceMatrixView;

    uint16_t bar = 0;
    ParameterViewMode mode = PARAM_MODE_BAR;

    int selectedFieldIndex = 0;
    LinkedList<ParameterField*>* visibleFields;

    LinkedList<ParameterField*> barFields;
    LinkedList<ParameterField*> channelFields;
    LinkedList<ParameterField*> eventFields;

    void renderFields();

    void setMode(ParameterViewMode _mode);
    void nextParameter();
    void prevParameter();
};

#endif
