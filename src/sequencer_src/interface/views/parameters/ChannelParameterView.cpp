#include "ChannelParameterView.h"

ChannelParameterView::ChannelParameterView() {
    fields.addComponent(&channelMuteField);
}

void ChannelParameterView::setChannel(SequenceChannel* channel) {
    this->channel = channel;
    channelMuteField.setValue(channel->getMute());
}
