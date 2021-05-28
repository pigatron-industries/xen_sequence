#include "ChannelParameterView.h"

ChannelParameterView::ChannelParameterView() {
    fields.addComponent(&midiChannelField);
    fields.addComponent(&channelMuteField);
    setSelectedField(0);
}

void ChannelParameterView::setChannel(SequenceChannel* channel) {
    this->channel = channel;
    midiChannelField.setValue(channel->getMidiChannel());
    channelMuteField.setValue(channel->getMute());
}

void ChannelParameterView::updateDataFromField(ParameterField* field) {
    if(field == &midiChannelField) {
        channel->setMidiChannel(midiChannelField.getValue());
    }
}