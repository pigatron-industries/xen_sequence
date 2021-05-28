#include "TickEventsParameterView.h"
#include "model/event/NoteEvent.h"
#include "model/AppData.h"
#include "lib/util/debug.h"

TickEventsParameterView::TickEventsParameterView() {
    for(int i = 0; i < MAX_EVENTS; i++) {
        eventParametersViews[i].addFields(&fields);
    }
    setSelectedField(0);
}

void TickEventsParameterView::setTickEvents(SequenceTickEvents* tickEvents, uint16_t barIndex, uint8_t channelIndex, uint8_t tickIndex) {
    this->tickEvents = tickEvents;
    this->barIndex = barIndex;
    this->channelIndex = channelIndex;
    this->tickIndex = tickIndex;

    if(tickEvents != NULL) {
        for(int i = 0; i < MAX_EVENTS; i++) {
            eventParametersViews[i].setEvent(tickEvents, tickEvents->getEvent(i));
        }
    } else {
        for(int i = 0; i < MAX_EVENTS; i++) {
            eventParametersViews[i].setEvent(NULL, NULL);
        }
    }
    if(selectedField != NULL && !selectedField->getVisibility() && fields.getComponent(0)->getVisibility()) {
        setSelectedField(0);
    }
}

int TickEventsParameterView::getSelectedEventIndex() {
    if(tickEvents != NULL) {
        for(int i = 0; i < MAX_EVENTS; i++) {
            if(eventParametersViews[i].containsField(selectedField)) {
                return i;
            }
        }
    }
    return -1;
}

EventParameterView* TickEventsParameterView::getSelectedEventParameters() {
    int index = getSelectedEventIndex();
    if(index != -1) {
        return &eventParametersViews[index];
    } else {
        return NULL;
    }
}

bool TickEventsParameterView::handleMidiEvent(const MidiMessage& message) {
    switch(message.command) {
        case COMMAND_NOTEON:
            return handleMidiMessage(message, EventType::NOTE_EVENT);
            break;
        case COMMAND_CONTROL_CHANGE:
            return handleMidiMessage(message, EventType::CONTROL_EVENT);
            break;
        default:
            return false;
    }
}

void TickEventsParameterView::updateDataFromField(ParameterField* field) {
    if(tickEvents != NULL) {
        for(int i = 0; i < MAX_EVENTS; i++) {
            eventParametersViews[i].updateDataFromField(field);
        }
        tickEvents->setCompiled(false);
    }
}

bool TickEventsParameterView::handleMidiMessage(const MidiMessage& message, EventType eventType) {
    bool newEvent = false;
    int eventIndex = getMatchingEventIndex(message);
    if(message.command == COMMAND_NOTEON) { 
        if(MidiState::midiState.getChannelState(message.channel).getNoteOnCount() == 1) {
            int nextEventIndex;
            while((nextEventIndex = getMatchingEventIndex(message, eventIndex+1)) != -1) {
                tickEvents->deleteEvent(nextEventIndex);
                newEvent = true;
            }
        } else {
            eventIndex = -1;
        }
    }

    if(eventIndex == -1) {
        eventIndex = createEvent(eventType);
        newEvent = true;
    }
    eventParametersViews[eventIndex].handleMidiEvent(message);
    return newEvent;
}

int TickEventsParameterView::getMatchingEventIndex(const MidiMessage& message, int startIndex) {
    if(tickEvents != NULL) {
        for(int i = startIndex; i < tickEvents->getSize(); i++) {
            SequenceEvent* event = tickEvents->getEvent(i);
            if(event->matchMessage(message)) {
                return i;
            }
        }
    }
    return -1;
}

int TickEventsParameterView::createEvent(EventType eventType) {
    SequenceEvent* event = AppData::data.newEvent(barIndex, channelIndex, tickIndex, eventType);
    if(tickEvents == NULL) {
        tickEvents = AppData::data.getTickEvents(barIndex, channelIndex, tickIndex);
    }
    int eventIndex = tickEvents->getEventIndex(event);
    eventParametersViews[eventIndex].setEvent(tickEvents, event);
    return eventIndex;
}