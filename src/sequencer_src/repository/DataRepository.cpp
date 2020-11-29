#include "DataRepository.h"

DataRepository DataRepository::data;

const String DataRepository::ROOT_DIRECTORY = String("/sequence");

void DataRepository::init() {
    if (!sd.begin(SdioConfig(FIFO_SDIO))) {
        Serial.println("SD card init failed");
        return;
    }

    if(!sd.exists(ROOT_DIRECTORY)) {
        Serial.println("Creating sequence directory");
        sd.mkdir(ROOT_DIRECTORY, true);
    }
}

void DataRepository::loadFileList(String directoryName) {
    File dir = sd.open(String(ROOT_DIRECTORY).concat(directoryName));
    if(dir.isDirectory()) {
        int i = 0;
        fileList.size = 0;
        File entry = dir.openNextFile();
        while(entry) {
            entry.getName(fileList.file[i].filename, MAX_FILENAME_SIZE);
            entry.close();
            fileList.size++;
            i++;
            entry = dir.openNextFile();
        }
    }
    dir.close();
}

void DataRepository::saveData() {
    SdFile file;
    sd.chdir("/sequence");
    Serial.println("Opening file");
    if(!file.open("test2.txt", FILE_WRITE)) {
        Serial.println("Open file failed!");
    }

    file.println("test data");
    file.sync();
    file.close();
}

void DataRepository::loadData() {

}