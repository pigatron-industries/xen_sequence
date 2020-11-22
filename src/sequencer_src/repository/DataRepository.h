#ifndef DataRepository_h
#define DataRepository_h

#include <SdFat.h>

#define MAX_FILENAME_SIZE 32

class DataRepository {
    public:
        static DataRepository data;

        void init();
        void saveData();
        void loadData();

    private:
        DataRepository() {}
        SdFat sd;

        void listFiles();
};

#endif