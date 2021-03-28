#include "ChannelParameterView.h"

ChannelParameterView::ChannelParameterView() {
    fields.addComponent(&channelMuteField);
    setSelectedField(0);
}

void ChannelParameterView::setChannel(SequenceChannel* channel) {
    this->channel = channel;
    channelMuteField.setValue(channel->getMute());
}

void ChannelParameterView::updateDataFromField(ParameterField* field) {
}