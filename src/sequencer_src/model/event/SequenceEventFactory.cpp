#include "SequenceEventFactory.h"

#include "NoteEvent.h"

SequenceEvent* SequenceEventFactory::create(EventType eventType) {
    switch(eventType) {
        case EventType::NOTE_EVENT:
            return new NoteEvent();
        case EventType::CONTROL_EVENT:
            return new NoteEvent(); //TODO
    }
    return NULL;
}
