#ifndef DataRepository_h
#define DataRepository_h

#include <SdFat.h>
#include "FileInfo.h"

class DataRepository {
    public:
        static DataRepository data;

        void init();

        void loadFileList(String directoryName);
        FileList& getFileList() { return fileList; }
        
        void saveData();
        void loadData();

    private:
        static const String ROOT_DIRECTORY;

        DataRepository() {}
        SdFat sd;

        FileList fileList;
};

#endif