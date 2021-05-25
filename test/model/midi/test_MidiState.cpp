#include <unity.h>
#include "sequencer_src/model/midi/MidiState.h"

void test_MidiChannelState_noteOn_one(void) {
    MidiChannelState state;
    state.noteOn(1);

    TEST_ASSERT_EQUAL_INT(1, state.getNoteOnCount());
    TEST_ASSERT_EQUAL_INT(1, state.getNoteOns()[0]);
}

void test_MidiChannelState_noteOn_multiple(void) {
    MidiChannelState state;
    state.noteOn(1);
    state.noteOn(2);
    state.noteOn(3);

    TEST_ASSERT_EQUAL_INT(3, state.getNoteOnCount());
    TEST_ASSERT_EQUAL_INT(1, state.getNoteOns()[0]);
    TEST_ASSERT_EQUAL_INT(2, state.getNoteOns()[1]);
    TEST_ASSERT_EQUAL_INT(3, state.getNoteOns()[2]);
}

void test_MidiChannelState_noteOn_max(void) {
    MidiChannelState state;
    state.noteOn(1);
    state.noteOn(2);
    state.noteOn(3);
    state.noteOn(4);
    state.noteOn(5);
    state.noteOn(6);

    TEST_ASSERT_EQUAL_INT(5, state.getNoteOnCount());
    TEST_ASSERT_EQUAL_INT(1, state.getNoteOns()[0]);
    TEST_ASSERT_EQUAL_INT(2, state.getNoteOns()[1]);
    TEST_ASSERT_EQUAL_INT(3, state.getNoteOns()[2]);
    TEST_ASSERT_EQUAL_INT(4, state.getNoteOns()[3]);
    TEST_ASSERT_EQUAL_INT(5, state.getNoteOns()[4]);
}


void test_MidiChannelState_noteOff_first(void) {
    MidiChannelState state;
    state.noteOn(1);
    state.noteOn(2);
    state.noteOn(3);
    state.noteOff(1);

    TEST_ASSERT_EQUAL_INT(2, state.getNoteOnCount());
    TEST_ASSERT_EQUAL_INT(2, state.getNoteOns()[0]);
    TEST_ASSERT_EQUAL_INT(3, state.getNoteOns()[1]);
}

void test_MidiChannelState_noteOff_middle(void) {
    MidiChannelState state;
    state.noteOn(1);
    state.noteOn(2);
    state.noteOn(3);
    state.noteOff(2);

    TEST_ASSERT_EQUAL_INT(2, state.getNoteOnCount());
    TEST_ASSERT_EQUAL_INT(1, state.getNoteOns()[0]);
    TEST_ASSERT_EQUAL_INT(3, state.getNoteOns()[1]);
}

void test_MidiChannelState_noteOff_last(void) {
    MidiChannelState state;
    state.noteOn(1);
    state.noteOn(2);
    state.noteOn(3);
    state.noteOff(3);

    TEST_ASSERT_EQUAL_INT(2, state.getNoteOnCount());
    TEST_ASSERT_EQUAL_INT(1, state.getNoteOns()[0]);
    TEST_ASSERT_EQUAL_INT(2, state.getNoteOns()[1]);
}

void test_MidiChannelState_noteOff_max(void) {
    MidiChannelState state;
    state.noteOn(1);
    state.noteOn(2);
    state.noteOn(3);
    state.noteOn(4);
    state.noteOn(5);
    state.noteOn(6);
    state.noteOff(5);

    TEST_ASSERT_EQUAL_INT(4, state.getNoteOnCount());
    TEST_ASSERT_EQUAL_INT(1, state.getNoteOns()[0]);
    TEST_ASSERT_EQUAL_INT(2, state.getNoteOns()[1]);
    TEST_ASSERT_EQUAL_INT(3, state.getNoteOns()[2]);
    TEST_ASSERT_EQUAL_INT(4, state.getNoteOns()[3]);
}

void test_MidiChannelState_noteOff_notExist(void) {
    MidiChannelState state;
    state.noteOn(1);
    state.noteOff(2);

    TEST_ASSERT_EQUAL_INT(1, state.getNoteOnCount());
    TEST_ASSERT_EQUAL_INT(1, state.getNoteOns()[0]);
}


int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_MidiChannelState_noteOn_one);
    RUN_TEST(test_MidiChannelState_noteOn_multiple);
    RUN_TEST(test_MidiChannelState_noteOn_max);
    RUN_TEST(test_MidiChannelState_noteOff_first);
    RUN_TEST(test_MidiChannelState_noteOff_middle);
    RUN_TEST(test_MidiChannelState_noteOff_last);
    RUN_TEST(test_MidiChannelState_noteOff_max);
    RUN_TEST(test_MidiChannelState_noteOff_notExist);
    UNITY_END();
    return 0;
}
