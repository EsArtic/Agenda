#ifndef AGENDASERVICE_H
#define AGENDASERVICE_H

#include "log.h"
#include "Storage.h"
#include "Reload.h"
#include <list>
#include <string>
using std::string;
using std::list;

class AgendaService {
    public:
        AgendaService();
        ~AgendaService();
        bool userLogIn(string userName, string password);
        bool userRegister(string userName, string password,
                          string email, string phone);
        bool deleteUser(string userName, string password);
        // a user can only delete itself
        list<User> listAllUsers(void);

        bool createMeeting(string userName, string title, string participator,
                           string startDate, string endDate);
        list<Meeting> meetingQuery(string userName, string title);
        list<Meeting> meetingQuery(string userName, string startDate,
                                   string endDate);
        list<Meeting> listAllMeetings(string userName);
        list<Meeting> listAllSponsorMeetings(string userName);
        list<Meeting> listAllParticipateMeetings(string userName);
        bool deleteMeeting(string userName, string title);
        bool deleteAllMeetings(string userName);

        void startAgenda();
        void quitAgenda();
        
        bool reloadUser(string date, string username);
        bool reloadMeeting(string date, string username);
    private:
        Storage* storage_;
        Reload* reload;
        Log log;
};

#endif
