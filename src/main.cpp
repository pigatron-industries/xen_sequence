#include <Arduino.h>

#include "hwconfig.h"

#include "lib/task/TaskManager.h"
#include "lib/drivers/Display.h"
#include "lib/drivers/LedMatrix.h"
#include "model/AppData.h"
#include "interface/InputTask.h"
#include "interface/InterfaceController.h"
#include "sequencer/Sequencer.h"
#include "sequencer/midi/MidiOutputService.h"

// hardware
Display display = Display();
LedMatrix ledMatrix = LedMatrix();

// data
AppData appData = AppData();

// sequencer
MidiOutputService midiOutputSevice = MidiOutputService(Serial2);
EventOutputService eventOutputService = EventOutputService(midiOutputSevice);
Sequencer sequencer = Sequencer(appData, eventOutputService);

// user interface
InterfaceController interfaceController = InterfaceController(appData, sequencer, display, ledMatrix);
InputTask inputTask = InputTask(interfaceController);


void setup() {
    Serial.begin(SERIAL_BAUD);
    Serial.println();
    Serial.println("=========================================");
    Serial.println("*      Pigatron Industries Sequence     *");
    Serial.println("=========================================");
    Serial.println();

    ledMatrix.init();
    inputTask.init();
    interfaceController.init();
}

void loop() {
    sequencer.execute();
    inputTask.execute();
}
