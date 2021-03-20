#include "ChannelParameterView.h"

ChannelParameterView::ChannelParameterView() {
    fields.addComponent(&channelMuteField);
    setSelectedField(0);
}

void ChannelParameterView::setChannel(SequenceChannel* channel) {
    this->channel = channel;
    channelMuteField.setValue(channel->getMute());
}

InterfaceEvent ChannelParameterView::handleEvent(InterfaceEvent event) {
    AbstractParameterView::handleEvent(event);
    switch(event.eventType) {
        case InterfaceEventType::DATA_DECREMENT:
        case InterfaceEventType::DATA_INCREMENT:
            updateDataFromField(selectedField);
            break;
        default:
            break;
    }
    return InterfaceEvent::NONE;
}

void ChannelParameterView::updateDataFromField(ParameterField* field) {
}