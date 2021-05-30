#include <Arduino.h>

#include "hwconfig.h"

#include "lib/task/TaskManager.h"
#include "lib/drivers/Display.h"
#include "lib/drivers/LedMatrix.h"
#include "lib/drivers/KeyboardLedMatrix.h"
#include "model/AppData.h"
#include "interface/Hardware.h"
#include "interface/InputTask.h"
#include "interface/InterfaceController.h"
#include "interface/Keyboard.h"
#include "sequencer/Sequencer.h"
#include "sequencer/midi/MidiOutputService.h"

#include "repository/DataRepository.h"

// sequencer
MidiOutputService midiOutputSevice = MidiOutputService(Serial3);

// user interface
InterfaceController interfaceController = InterfaceController();
InputTask inputTask = InputTask(interfaceController);


void setup() {
    Serial.begin(SERIAL_BAUD);
    Serial.println();
    Serial.println("=========================================");
    Serial.println("*      Pigatron Industries Sequence     *");
    Serial.println("=========================================");
    Serial.println();

    Hardware::init();
    DataRepository::data.init();
    Sequencer::sequencer.init(&midiOutputSevice);
    inputTask.init();
    interfaceController.init();
    midiOutputSevice.init();
}

void loop() {
    inputTask.execute();
}
