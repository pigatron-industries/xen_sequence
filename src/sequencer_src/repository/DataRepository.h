#ifndef DataRepository_h
#define DataRepository_h

#include <SdFat.h>
#include "FileInfo.h"

#define MAX_FILE_COUNT 32

class DataRepository {
    public:
        static DataRepository data;

        void init();

        void loadFileList(char* directoryName);
        FileList& getFileList() { return fileList; }
        
        void saveData();
        void loadData();

        void listFiles(); //TEST FUNCTION

    private:
        DataRepository() {}
        SdFat sd;

        FileList fileList;
};

#endif