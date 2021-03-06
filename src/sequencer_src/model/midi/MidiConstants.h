#ifndef MidiConstants_h
#define MidiConstants_h

// command
#define COMMAND_NONE 0
#define COMMAND_NOTEOFF 0x8
#define COMMAND_NOTEON 0x9
#define COMMAND_POLY_PRESSURE 0xA
#define COMMAND_CONTROL_CHANGE 0xB
#define COMMAND_PROGRAM_CHANGE 0xC
#define COMMAND_CHAN_PRESSURE 0xD
#define COMMAND_PITCH_BEND 0xE
#define COMMAND_SYSTEM 0xF

// channel
#define SYSTEM_EXCLUSIVE 0x0
#define SYSTEM_SONG_POSITION 0x2
#define SYSTEM_CLOCK 0x8
#define SYSTEM_START 0xA
#define SYSTEM_CONTINUE 0xA
#define SYSTEM_STOP 0xC
#define SYSTEM_RESET 0xF

#define SYSTEM_EXCLUSIVE_ID 0x7D
#define SYSTEM_EXCLUSIVE_END 0xF7

#endif
