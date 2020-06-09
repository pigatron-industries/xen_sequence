#include <Arduino.h>

#include "hwconfig.h"

#include "lib/task/TaskManager.h"
#include "lib/drivers/Display.h"
#include "lib/drivers/LedMatrix.h"
#include "model/AppData.h"
#include "interface/InputTask.h"
#include "interface/InterfaceController.h"



// hardware
Display display = Display();
LedMatrix ledMatrix = LedMatrix();

// data
AppData appData = AppData();

// user interface
InterfaceController interfaceController = InterfaceController(appData, display, ledMatrix);
InputTask inputTask = InputTask(interfaceController);



void setup() {
    Serial.begin(SERIAL_BAUD);
    Serial.println();
    Serial.println("=========================================");
    Serial.println("*      Pigatron Industries Sequence     *");
    Serial.println("=========================================");
    Serial.println();

    appData.populateTestData();
    ledMatrix.init();
    inputTask.init();
    interfaceController.init();
}

void loop() {
    inputTask.execute();
}
