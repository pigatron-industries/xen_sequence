#include <Arduino.h>

#include "hwconfig.h"

#include "lib/task/TaskManager.h"
#include "lib/drivers/Display.h"
#include "lib/drivers/LedMatrix.h"
#include "model/AppData.h"
#include "interface/InputTask.h"
#include "interface/InterfaceController.h"
#include "sequencer/Sequencer.h"
#include "lib/util/StopWatch.h"

// hardware
Display display = Display();
LedMatrix ledMatrix = LedMatrix();

// data
AppData appData = AppData();

// sequencer
Sequencer sequencer = Sequencer(appData);

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
