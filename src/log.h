#ifndef LOG_H
#define LOG_H

#include"Date.h"
#include<map>
#include<string>
#include <time.h>
using std::map;
using std::string;

class Log {

    private:
        map<string, string> log;

    public:
        Log();
        ~Log();
        void readFromFile(const char* fpath);
        void write(string str);
        void writeToFile(const char* fpath);
        time_t nowtime;
};

#endif
