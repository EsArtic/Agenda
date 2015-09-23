#ifndef AGENDA_STORAGE_H
#define AGENDA_STORAGE_H

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
        TypeName(const TypeName&); \
        void operator=(const TypeName&)

#include <list>
#include <string>
#include <functional>
#include "User.h"
#include "Meeting.h"

using std::list;
using std::function;

class Storage {
        
    public:
        // singleton
        static Storage *getInstance();
        ~Storage();
        // CRUD for User & Meeting
        // using C++11 Function Template and Lambda Expressions
        void createUser(const User&);
        list<User> queryUser(function<bool(const User&)> filter);
        // return found users

        int updateUser(function<bool(const User&)> filter,
        std::function<void(User&)> switcher);
        // return the number of updated users

        list<User> deleteUser(function<bool(const User&)> filter);
        // return the number of deleted users

        void createMeeting(const Meeting&);
        list<Meeting> queryMeeting(function<bool(const Meeting&)> filter);
        // return found meetings
        int updateMeeting(function<bool(const Meeting&)> filter,
        function<void(Meeting&)> switcher);
        // return the number of updated meetings
        list<Meeting> deleteMeeting(function<bool(const Meeting&)> filter);
        // return the number of deleted meetings
        // File IO
        bool sync();

    private:
        static Storage* instance_;

        Storage();

        list<User> userList_;
        list<Meeting> meetingList_;
        // File IO
        bool readFromFile(const char *fpath);
        bool writeToFile(const char *fpath);

        DISALLOW_COPY_AND_ASSIGN(Storage);
};

#endif
