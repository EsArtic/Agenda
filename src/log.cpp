#include"log.h"
#include<fstream>
#include<iostream>
#include <time.h>
using std::endl;
using std::cout;
using std::ifstream;
using std::ofstream;

Log::Log() {
    readFromFile("Log.txt");
}
Log::~Log() {
    writeToFile("Log.txt");
}
void Log::write(string str) {
    nowtime = time(NULL);
    struct tm *ntime = localtime(&nowtime);

    int year = ntime->tm_year+1900;
    int month = ntime->tm_mon+1;
    int day = ntime->tm_mday;
    int hour = ntime->tm_hour;
    int minute = ntime->tm_min;
    int sec = ntime->tm_sec;

    Date t(year, month, day, hour, minute);
    string key = Date::dateToString(t);
    key += ":";
    key += (sec/10+'0');
    key += (sec%10+'0');
    log[key] = str;
}
void Log::readFromFile(const char* fpath) {
    ifstream in(fpath);

    string time, elem, block;

    while (!in.eof()) {
        getline(in, time);
        if (time != "") {
            getline(in, elem);
            time.erase(0,1);
            elem.erase(0,1);
            log[time] = elem;
            getline(in, block);
        }
    }
    in.close();
}
void Log::writeToFile(const char* fpath) {
    ofstream out(fpath);
    
    map<string, string>::iterator it = log.begin();
    while (it != log.end()) {
        out << " " << it->first << endl;
        out << " " << it->second << endl;
        out << "--------------------------------------------------" << endl;
        it++;
    }
    out.close();
}
        
