#ifndef Reload_H
#define Reload_H

#include"Storage.h"
#include<list>
#include<map>
#include<string>
#include <time.h>
using std::list;
using std::string;
using std::map;

class Reload {
    public:
        static Reload *getInstance();
        ~Reload();
        bool reloadUser(string date, string username, Storage* storage_);
        bool reloadMeeting(string date, string username, Storage* storage_);
        void write(User U);
        void write(Meeting M);
        time_t nowtime;

    private:
        bool readFromFile(const char *Ufpath, const char *Mfpath);
        bool writeToFile(const char *Ufpath, const char *Mfpath);
        map<string, User> userM;
        map<string, Meeting> meetingM;
        
        static Reload* instance_;
        Reload();
};

#endif
