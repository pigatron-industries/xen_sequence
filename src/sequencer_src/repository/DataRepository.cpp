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

void DataRepository::saveSequence(String path) {
    String fullpath = String(ROOT_DIRECTORY).concat(path);
    Serial.println("Saving to ");
    Serial.println(fullpath);

    char jsonBuffer[JSON_BUF_SIZE];
    serializeSequence(jsonBuffer, JSON_BUF_SIZE);
    Serial.println(jsonBuffer);

    SdFile file;
    if(!file.open(fullpath.c_str(), O_WRONLY | O_CREAT | O_TRUNC)) {
        Serial.println("Open file failed!");
    }
    file.println(jsonBuffer);
    file.sync();
    file.close();
    Serial.println("done.");
    Serial.println();
}

void DataRepository::loadSequence(String path) {
    String fullpath = String(ROOT_DIRECTORY).concat(path);
    Serial.println("Loading from ");
    Serial.println(fullpath);

    SdFile file;
    if(!file.open(fullpath.c_str(), FILE_READ)) {
        Serial.println("Open file failed!");
    }

    char jsonBuffer[JSON_BUF_SIZE];
    int size = file.read(jsonBuffer, JSON_BUF_SIZE);
    Serial.write(jsonBuffer, size);

    deserializeSequence(jsonBuffer, size);

    file.close();
    Serial.println("done.");
    Serial.println();
}

size_t DataRepository::serializeSequence(char* buffer, size_t bufferSize) {
    DynamicJsonDocument doc(JSON_DOC_SIZE);

    doc["test"] = 43;

    return serializeJson(doc, buffer, bufferSize);
}

void DataRepository::deserializeSequence(char* buffer, size_t size) {
    DynamicJsonDocument doc(JSON_DOC_SIZE);
    deserializeJson(doc, buffer, size);

    int test = doc["test"];

    Serial.println(test);
}