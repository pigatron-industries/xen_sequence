#include "ParameterView.h"
#include "interface/Hardware.h"
#include "model/AppData.h"
#include "lib/util/debug.h"

#include "Org_01.h"

ParameterView::ParameterView(Sequencer& _sequencer, SequenceMatrixView& _sequenceMatrixView) :
    sequencer(_sequencer),
    sequenceMatrixView(_sequenceMatrixView) {
    songFields.addComponent(&songSpeedField);
    songFields.addComponent(&songSpeedMultField);
    barFields.addComponent(&barLengthField);
    barFields.addComponent(&barSpeedField);
    barFields.addComponent(&barSpeedMultField);
    channelFields.addComponent(&channelMuteField);
    eventFields.addComponent(&eventPitchField);
    eventFields.addComponent(&eventVelocityField);
    eventFields.addComponent(&eventGateField);
    eventFields.addComponent(&eventDelayField);
    Hardware::midiInputService.addEventHandler(this);
}

void ParameterView::init() {
    DEBUG("ParameterView::init")
    barIndex = sequencer.getBarIndex();
    updateSongFields();
    updateSelectedBarFields();
    setParameterViewMode(parameterViewMode);
}

void ParameterView::render(GraphicsContext& g) {
    DEBUG("ParameterView::render");
    renderMode();

    g.yPos += FIELD_HEIGHT;
    visibleFields->render(g);

    sequenceMatrixView.render();

    dirtyScreen = false;
}

void ParameterView::renderMode() {
    uint8_t top = 0;
    Hardware::display.setTextColour(Colour::WHITE);
    Hardware::display.setCursor(0, top+TEXT_HEIGHT);
    Hardware::display.print(parameterViewMode == PARAM_MODE_SONG ? "SONG" : 
                            parameterViewMode == PARAM_MODE_BAR ? "BAR" : 
                            parameterViewMode == PARAM_MODE_CHANNEL ? "CHANNEL" : "EVENT");
}

void ParameterView::setDirtyScreen() {
    dirtyScreen = true;
    // for(int i = 0; i < visibleFields->size(); i++) {
    //     visibleFields->get(i)->setDirty();
    // }
}

void ParameterView::renderKeyLeds() {
    if(selectionMode == ParameterViewSelectionMode::SELECT_EVENT) {
        if(selectedEvent != NULL) {
            Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_COPY, LedColour::BLUE);
            Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_ADD_DEL, LedColour::RED);
        } else {
            Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_COPY, LedColour::OFF);
            Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_ADD_DEL, LedColour::BLUE);
        }
    } else if (selectionMode == ParameterViewSelectionMode::SELECT_CHANNEL) {
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_COPY, LedColour::BLUE);
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_ADD_DEL, LedColour::RED);
    }
}

void ParameterView::handleMidiEvent(MidiMessage message) {
    if(recording && parameterViewMode == PARAM_MODE_EVENT) {
        DEBUG("ParameterView::handleMidiEvent");
        if(message.command == COMMAND_NOTEON) {
            Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_RECORD, LedColour::OFF);
            if(selectedEvent == NULL) {
                addEvent();
            }
            eventPitchField.setValue(message.data1);
            eventVelocityField.setValue(message.data2);
            updateDataFromField(&eventPitchField);
            updateDataFromField(&eventVelocityField);

            //TODO advance to next tick depending on recoding mode

            View::render(false);
        } else if (message.command == COMMAND_NOTEOFF) {
            Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_RECORD, LedColour::RED);
        }
    }
}

InterfaceEvent ParameterView::handleEvent(InterfaceEvent event) {
    DEBUG("ParameterView::handleEvent");
    switch(event.eventType) {
        case InterfaceEventType::STICK_UP:
            cursorUp();
            break;

        case InterfaceEventType::STICK_DOWN:
            cursorDown();
            break;

        case InterfaceEventType::STICK_LEFT:
            cursorLeft();
            break;

        case InterfaceEventType::STICK_RIGHT:
            cursorRight();
            break;

        case InterfaceEventType::DATA_PRESS:
            nextParameter();
            View::render();
            break;

        case InterfaceEventType::DATA_INCREMENT:
            fieldIncrement(event.data);
            break;

        case InterfaceEventType::DATA_DECREMENT:
            fieldDecrement(event.data);
            break;

        case InterfaceEventType::KEY_RECORD: 
            if(event.data == EVENT_KEY_PRESSED) {
                record(!recording);
            }
            break;

        case InterfaceEventType::KEY_SELECTION:
        case InterfaceEventType::STICK_PRESS:
            if(event.data == EVENT_KEY_PRESSED) {
                cycleParameterViewMode();
                View::render();
            }
            break;

        case InterfaceEventType::KEY_ADD_DEL:
            if(event.data == EVENT_KEY_PRESSED) {
                if(selectionMode == ParameterViewSelectionMode::SELECT_EVENT) {
                    if(selectedEvent == NULL) {
                        addEvent();
                    } else {
                        deleteEvent();
                    }
                } else if (selectionMode == ParameterViewSelectionMode::SELECT_CHANNEL) {
                    clearPattern();
                }
            }
            break;

        case InterfaceEventType::KEY_PREV:
            if(event.data == EVENT_KEY_PRESSED) {
                prevBar();
            }
            break;
        case InterfaceEventType::KEY_NEXT:
            if(event.data == EVENT_KEY_PRESSED) {
                nextBar();
            }
            break;

        case InterfaceEventType::KEY_COPY:
            if(event.data == EVENT_KEY_PRESSED) {
                copy();
            }
            break;

        case InterfaceEventType::KEY_PASTE:
            if(event.data == EVENT_KEY_PRESSED) {
                paste();
            }
            break;

        case InterfaceEventType::KEY_MOVE:
            if(event.data == EVENT_KEY_PRESSED) {
                drag();
            } else if(event.data == EVENT_KEY_RELEASED) {
                drop();
            }
            break;

        default:
            break;
    }


    return InterfaceEvent::NONE;
}

void ParameterView::record(bool value) {
    recording = value;
    Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_RECORD, value ? LedColour::RED : LedColour::OFF);
}

void ParameterView::cursorUp() {
    sequenceMatrixView.cursorUp();
    updateSelectedChannelFields();
    updateSelectedEventFields();
    View::render();
}

void ParameterView::cursorDown() {
    sequenceMatrixView.cursorDown();
    updateSelectedChannelFields();
    updateSelectedEventFields();
    View::render();
}

void ParameterView::cursorLeft() {
    sequenceMatrixView.cursorLeft();
    updateSelectedEventFields();
    View::render();
}

void ParameterView::cursorRight() {
    sequenceMatrixView.cursorRight();
    updateSelectedEventFields();
    View::render();
}

void ParameterView::nextBar() {
    barIndex = sequencer.nextBar();
    updateSelectedBarFields();
    updateSelectedEventFields();
    queueRender();
}

void ParameterView::prevBar() {
    barIndex = sequencer.prevBar();
    updateSelectedBarFields();
    updateSelectedEventFields();
    queueRender();
}

void ParameterView::fieldIncrement(int amount) {
    ParameterField* field = getSelectedField();
    if(field != NULL) {
        field->increment(amount);
        updateDataFromField(field);
        queueRender();
    }
}

void ParameterView::fieldDecrement(int amount) {
    ParameterField* field = getSelectedField();
    if(field != NULL) {
        field->decrement(amount);
        updateDataFromField(field);
        queueRender();
    }
}

void ParameterView::setSelectedField(int8_t fieldIndex) {
    selectedFieldIndex = fieldIndex;
    if(selectedField != NULL) {
        selectedField->setSelected(false);
    }
    if(selectedFieldIndex >= 0 && visibleFields->getSize() > selectedFieldIndex) {
        selectedField = (ParameterField*)visibleFields->getComponent(selectedFieldIndex);
        selectedField->setSelected(true);
    } else {
        selectedField = NULL;
    }
}

ParameterField* ParameterView::getSelectedField() {
    if(selectedFieldIndex >= 0 && visibleFields->getSize() > selectedFieldIndex) {
        return (ParameterField*)visibleFields->getComponent(selectedFieldIndex);
    } else {
        return NULL;
    }
}

void ParameterView::nextParameter() {
    int8_t newFieldIndex = selectedFieldIndex+1;
    if(newFieldIndex >= visibleFields->getSize()) {
        newFieldIndex = 0;
    }
    setSelectedField(newFieldIndex);
}

void ParameterView::prevParameter() {
    int8_t newFieldIndex = selectedFieldIndex-1;
    if(newFieldIndex < 0) {
        newFieldIndex = visibleFields->getSize()-1;
    }
    setSelectedField(newFieldIndex);
}

void ParameterView::setBar(uint16_t _barIndex) {
    barIndex = _barIndex;
    sequenceMatrixView.setBar(barIndex);
    updateSelectedBarFields();
};

void ParameterView::cycleSelectionMode() {
    switch(parameterViewMode) {
        case PARAM_MODE_SONG:
        case PARAM_MODE_BAR:
            setSelectionMode(ParameterViewSelectionMode::SELECT_NONE);
            break;
        case PARAM_MODE_CHANNEL:
            setSelectionMode(ParameterViewSelectionMode::SELECT_CHANNEL);
            break;
        case PARAM_MODE_EVENT:
            setSelectionMode(ParameterViewSelectionMode::SELECT_EVENT);
            break;
    }
}

void ParameterView::setSelectionMode(ParameterViewSelectionMode _selectionMode) {
    selectionMode = _selectionMode;
    if(selectionMode == ParameterViewSelectionMode::SELECT_EVENT || selectionMode == ParameterViewSelectionMode::SELECT_CHANNEL) {
        sequenceMatrixView.setSelectionActive(true);
    } else {
        sequenceMatrixView.setSelectionActive(false);
    }
}

void ParameterView::cycleParameterViewMode() {
    setParameterViewMode(parameterViewMode == PARAM_MODE_SONG ? PARAM_MODE_BAR :
                         parameterViewMode == PARAM_MODE_BAR ? PARAM_MODE_CHANNEL :
                         parameterViewMode == PARAM_MODE_CHANNEL ? PARAM_MODE_EVENT : PARAM_MODE_SONG);
}

void ParameterView::setParameterViewMode(ParameterViewMode parameterViewMode) {
    DEBUG("ParameterView::setParameterViewMode"); 
    DEBUG(parameterViewMode);
    this->parameterViewMode = parameterViewMode;
    switch(parameterViewMode) {
        case PARAM_MODE_SONG:
            visibleFields = &songFields;
            sequenceMatrixView.setSelectionMode(SequenceMatrixSelectionMode::SELECT_NONE);
            setSelectionMode(ParameterViewSelectionMode::SELECT_NONE);
            break;
        case PARAM_MODE_BAR:
            visibleFields = &barFields;
            sequenceMatrixView.setSelectionMode(SequenceMatrixSelectionMode::SELECT_NONE);
            setSelectionMode(ParameterViewSelectionMode::SELECT_NONE);
            break;
        case PARAM_MODE_CHANNEL:
            visibleFields = &channelFields;
            sequenceMatrixView.setSelectionMode(SequenceMatrixSelectionMode::SELECT_CHANNEL);
            setSelectionMode(ParameterViewSelectionMode::SELECT_CHANNEL);
            break;
        case PARAM_MODE_EVENT:
            visibleFields = &eventFields;
            sequenceMatrixView.setSelectionMode(SequenceMatrixSelectionMode::SELECT_EVENT);
            setSelectionMode(ParameterViewSelectionMode::SELECT_EVENT);
            updateSelectedEventFields();
            break;
    };
    setSelectedField(visibleFields->getSize() == 0 ? -1 : 0);
    renderKeyLeds();
    queueRender(true);
}

void ParameterView::updateSongFields() {
    songSpeedField.setValue(AppData::data.getSequence().getSpeed());
    songSpeedMultField.setValue(AppData::data.getSequence().getSpeedMult());
}

void ParameterView::updateSelectedBarFields() {
    bar = AppData::data.getBar(barIndex);
    barLengthField.setValue(bar->getLength());
    barSpeedField.setValue(bar->getSpeedDiff());
    barSpeedMultField.setValue(bar->getSpeedMult());
    sequenceMatrixView.setBar(barIndex);
}

void ParameterView::updateSelectedChannelFields() {
    selectedPattern = bar->getPattern(sequenceMatrixView.getSelectCursorChannel());
    SequenceChannel selectedChannel = AppData::data.getChannel(sequenceMatrixView.getSelectCursorChannel());
    channelMuteField.setValue(selectedChannel.getMute());
}

void ParameterView::updateSelectedEventFields() {
    updateSelectedChannelFields();
    if(selectedPattern != NULL) {
        selectedEvent = selectedPattern->getEvent(sequenceMatrixView.getSelectCursorTick());
    } else {
        selectedEvent = NULL;
    }
    if(selectedEvent != NULL) {
        eventPitchField.setValue(selectedEvent->getPitch());
        eventVelocityField.setValue(selectedEvent->getVelocity());
        eventGateField.setValue(selectedEvent->getGate());
        eventDelayField.setValue(selectedEvent->getDelay());
        for(int i = 0; i < eventFields.getSize(); i++) {
            eventFields.getComponent(i)->setVisibility(true);
        }
    } else {
        for(int i = 0; i < eventFields.getSize(); i++) {
            eventFields.getComponent(i)->setVisibility(false);
        }
    }

    renderKeyLeds();
    queueRender(true);
}

void ParameterView::updateDataFromField(ParameterField* field) {
    if(selectedEvent != NULL) {
        if(field == &eventPitchField) {
            selectedEvent->setPitch(eventPitchField.getValue());
        } else if(field == &eventVelocityField) {
            selectedEvent->setVelocity(eventVelocityField.getValue());
        } else if(field == &eventGateField) {
            selectedEvent->setGate(eventGateField.getValue());
        } else if(field == &eventDelayField) {
            selectedEvent->setDelay(eventDelayField.getValue());
        }
    }
    if(field == &barSpeedField) {
        bar->setSpeedDiff(barSpeedField.getValue());
        if(sequencer.getBarIndex() == barIndex) {
            sequencer.updateBarSpeed();
        }
    } else if(field == &barSpeedMultField) {
        bar->setSpeedMult(barSpeedMultField.getValue());
        if(sequencer.getBarIndex() == barIndex) {
            sequencer.updateBarSpeed();
        }
    } else if(field == &songSpeedField) {
        AppData::data.getSequence().setSpeed(songSpeedField.getValue());
        if(sequencer.getBarIndex() == barIndex) {
            sequencer.updateBarSpeed();
        }
    } else if(field == &songSpeedMultField) {
        AppData::data.getSequence().setSpeedMult(songSpeedMultField.getValue());
        if(sequencer.getBarIndex() == barIndex) {
            sequencer.updateBarSpeed();
        }
    }
}

void ParameterView::addEvent() {
    AppData::data.newEvent(barIndex, sequenceMatrixView.getSelectCursorChannel(), sequenceMatrixView.getSelectCursorTick());
    updateSelectedEventFields();
}

void ParameterView::addEvent(SequenceEvent* copy) {
    AppData::data.newEvent(barIndex, sequenceMatrixView.getSelectCursorChannel(), sequenceMatrixView.getSelectCursorTick(), copy);
    updateSelectedEventFields();
}

void ParameterView::deleteEvent() {
    AppData::data.deleteEvent(barIndex, sequenceMatrixView.getSelectCursorChannel(), sequenceMatrixView.getSelectCursorTick());
    updateSelectedEventFields();
}

void ParameterView::clearPattern() {
    if(selectedPattern != NULL) {
        selectedPattern->clear();
        queueRender();
    }
}

void ParameterView::copy() {
    if(selectionMode == ParameterViewSelectionMode::SELECT_EVENT) {
        if(selectedEvent != NULL) {
            if(copiedEvent != NULL) {
                delete copiedEvent;
            }
            copiedEvent = new SequenceEvent(selectedEvent);
            Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_PASTE, LedColour::BLUE);
            Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_COPY, LedColour::OFF);
        }
    }
}

void ParameterView::paste() {
    if(selectionMode == ParameterViewSelectionMode::SELECT_EVENT) {
        if(copiedEvent != NULL) {
            deleteEvent();
            addEvent(copiedEvent);
        }
    }
}

void ParameterView::drag() {
    if(selectionMode == ParameterViewSelectionMode::SELECT_EVENT && selectedEvent != NULL) {
        copiedEvent = new SequenceEvent(selectedEvent);
        dragging = true;
        draggingFromBar = barIndex;
        draggingFromChannel = sequenceMatrixView.getSelectCursorChannel();
        draggingFromTick = sequenceMatrixView.getSelectCursorTick();
        sequenceMatrixView.setMarker(draggingFromChannel, draggingFromTick);
        Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_MOVE, LedColour::BLUE);
    }
}

void ParameterView::drop() {
    if(dragging) {
        if(selectionMode == ParameterViewSelectionMode::SELECT_EVENT && copiedEvent != NULL) {
            AppData::data.deleteEvent(draggingFromBar, draggingFromChannel, draggingFromTick);
            addEvent(copiedEvent);
        }
    }

    sequenceMatrixView.clearMarker();
    Hardware::keyboard.setKeyLed(InterfaceEventType::KEY_MOVE, LedColour::OFF);
    dragging = false;
}