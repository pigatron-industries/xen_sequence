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

    listFiles();
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
            entry = dir.openNextFile();
        }
    }
}

void DataRepository::listFiles() {
    loadFileList("/sequence");
    for(int i = 0; i < fileList.size; i++) {
        Serial.println(fileList.file[i].filename);
    }
}

void DataRepository::saveData() {
    SdFile file;
    // sd.chdir("/sequence");
    // file.open("text.txt", FILE_WRITE);
    // file.println("test data");
    // file.close();
}

void DataRepository::loadData() {

}