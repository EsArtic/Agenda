#include"AgendaService.h"
#include<iostream>
using std::cout;
using std::endl;

AgendaService::AgendaService() {
    startAgenda();
    reload = Reload::getInstance();
    string str = "Start Agenda";
    log.write(str);
}
AgendaService::~AgendaService() {
    quitAgenda();
    string str = "Quit Agenda";
    log.write(str);
    delete storage_;
    delete reload;
}
bool AgendaService::reloadUser(string date, string userName) {
    list<User> l = storage_->queryUser([&](User U)->bool {
        if (U.getName() == userName) return true;
        return false;});
    if (l.size()) {
        return false;
    } else {
        if (reload->reloadUser(date, userName, storage_)) {
            string str = "Reload User--"+userName;
            log.write(str);
            return true;
        }
        return false;
    }
}
bool AgendaService::reloadMeeting(string date, string username) {
    list<User> l = storage_->queryUser([&](User U)->bool {
        if (U.getName() == username) return true;
        return false;});
    if (l.size()) {
        if (reload->reloadMeeting(date, username, storage_)) {
            string str = "Reload Meetings--"+username;
            log.write(str);
            return true;
        }
        return false;
    } else {
        return false;
    }
}
bool AgendaService::userLogIn(string userName, string password) {
    list<User> l = storage_->queryUser([&](User U)->bool {
        if ((U.getName() == userName)&&(U.getPassword() == password))
            return true;
        return false;});
    if (l.size() == 0) {
        string str = userName+" log in fail";
        log.write(str);
        return false;
    } else {
        string str = userName+" log in";
        log.write(str);
        return true;
    }
}
bool AgendaService::userRegister(string userName, string password,
                                 string email, string phone) {
    User u(userName, password, email, phone);
    list<User> l = storage_->queryUser([&](User U)->bool {
        if (U.getName() == userName) return true;
        return false;});
    if (l.size() == 0) {
        storage_->createUser(u);
        string str = userName+" registed";
        log.write(str);
        return true;
    } else {
        string str = userName+" register fail";
        log.write(str);
        return false;
    }
}
bool AgendaService::deleteUser(string userName, string password) {
    list<User> u = storage_->deleteUser([&](User U)->bool {
        if ((U.getName() == userName)&&(U.getPassword() == password))
            return true;
        return false;});
    if (u.size()) {
        list<User>::iterator ut = u.begin();
        while (ut != u.end()) {
            reload->write(*ut);
            ut++;
        }
        list<Meeting> l = storage_->deleteMeeting([&](Meeting M)->bool {
            if (M.getSponsor() == userName) return true;
            if (M.getParticipator() == userName) return true;
            return false;});
        list<Meeting>::iterator it = l.begin();
        while (it != l.end()) {
            reload->write(*it);
            it++;
        }
        string str = "DeleteUser-name: "+userName;
        log.write(str);
        return true;
    } else {
        string str = "DeleteUser fail-name: "+userName;
        log.write(str);
        return false;
    }
}
// a user can only delete itself
list<User> AgendaService::listAllUsers() {
    return storage_->queryUser([&](User U)->bool {return true;});
}

bool AgendaService::createMeeting(string userName, string title,
             string participator, string startDate, string endDate) {
    Date StartDate = Date::stringToDate(startDate);
    Date EndDate = Date::stringToDate(endDate);
    // judge whether date is valid
    if (!Date::isValid(StartDate)) return false;
    if (!Date::isValid(EndDate)) return false;

    // judge whether participator is user itself
    if (userName == participator) return false;

    // judge whether participator is eixst
    list<User> l = storage_->queryUser([&](User U)->bool {
        if (U.getName() == participator) return true;
        return false;});
    if (l.size() == 0) return false;
    
    // judge whether user is eixst
    list<User> l2 = storage_->queryUser([&](User U)->bool {
        if (U.getName() == userName) return true;
        return false;});
    if (l2.size() == 0) return false;

    // judge whether the title and the time is valid
    list<Meeting> m1 = storage_->queryMeeting([&](Meeting M)->bool {
        if (M.getSponsor() == userName) return true;
        if (M.getParticipator() == userName) return true;
        return false;});
    int num = 1;
    list<Meeting>::iterator mt = m1.begin();
    while (mt != m1.end()) {
        if (!((mt->getEndDate() <= StartDate)||
              (mt->getStartDate() >= EndDate))) {
            num++;
        }
        if (mt->getTitle() == title) num++;
        mt++;
    }
    if (num > 1) return false;

    list<Meeting> m2 = storage_->queryMeeting([&](Meeting M)->bool {
        if (M.getSponsor() == participator) return true;
        if (M.getParticipator() == participator) return true;
        return false;});
    num = 1;
    mt = m2.begin();
    while (mt != m2.end()) {
        if (!((mt->getEndDate() <= StartDate)||
              (mt->getStartDate() >= EndDate))) {
            num++;
        }
        if (mt->getTitle() == title) num++;
        mt++;
    }
    if (num > 1) return false;

    if (StartDate >= EndDate) return false;

    Meeting M(userName, participator, StartDate, EndDate, title);
    storage_->createMeeting(M);
    string str = "Create Meeting-";
    str += (" Title: "+title);
    str += (" User: "+userName);
    str += (" Participator: "+participator);
    str += (" StartDate: "+Date::dateToString(StartDate));
    str += (" EndDate: "+Date::dateToString(EndDate));
    log.write(str);
    return true;
}

list<Meeting> AgendaService::meetingQuery(string userName, string title) {
    list<Meeting> ans = storage_->queryMeeting([&](Meeting M)->bool {
        if (M.getSponsor() == userName) {
            if (M.getTitle() == title) return true;
        }
        if (M.getParticipator() == userName) {
            if (M.getTitle() == title) return true;
        }
        return false;});
    return ans;
}
list<Meeting> AgendaService::meetingQuery(string userName, string startDate,
                                          string endDate) {
    Date StartDate = Date::stringToDate(startDate);
    Date EndDate = Date::stringToDate(endDate);

    list<Meeting> ans = storage_->queryMeeting([&](Meeting M)->bool {
        if (M.getSponsor() == userName) {
            if (!((M.getEndDate() < StartDate)||(M.getStartDate() > EndDate))) {
                return true;
            }
        }
        if (M.getParticipator() == userName) {
            if (!((M.getEndDate() < StartDate)||(M.getStartDate() > EndDate))) {
                return true;
            }
        }
        return false;});
    return ans;
}
list<Meeting> AgendaService::listAllMeetings(string userName) {
    return storage_->queryMeeting([&](Meeting M)->bool {
        if (M.getSponsor() == userName) return true;
        if (M.getParticipator() == userName) return true;
        return false;});
}
list<Meeting> AgendaService::listAllSponsorMeetings(string userName) {
    list<Meeting> ans = storage_->queryMeeting([&](Meeting M)->bool {
        if (M.getSponsor() == userName) return true;
        return false;});
    return ans;
}
list<Meeting> AgendaService::listAllParticipateMeetings(string userName) {
    list<Meeting> ans = storage_->queryMeeting([&](Meeting M)->bool {
        if (M.getParticipator() == userName) return true;
        return false;});
    return ans;
}
bool AgendaService::deleteMeeting(string userName, string title) {
    list<Meeting> l = storage_->deleteMeeting([&](Meeting M)->bool {
        if (M.getTitle() == title) {
            if (M.getSponsor() == userName) return true;
        }
        return false;});
    if (l.size()) {
        list<Meeting>::iterator it = l.begin();
        while (it != l.end()) {
            reload->write(*it);
            it++;
        }
        string str = "Delete Meeting-";
        str += (" Title: "+title);
        str += (" User: "+userName);
        log.write(str);
        return true;
    } else {
        string str = "Delete Meeting fail-";
        str += (" Title: "+title);
        str += (" User: "+userName);
        log.write(str);
        return false;
    }
}
bool AgendaService::deleteAllMeetings(string userName) {
    list<Meeting> l = storage_->deleteMeeting([&](Meeting M)->bool {
        if (M.getSponsor() == userName) return true;
        return false;});
    if (l.size()) {
        list<Meeting>::iterator it = l.begin();
        while (it != l.end()) {
            reload->write(*it);
            it++;
        }
        string str = "Delete All Meeting-";
        str += (" User: "+userName);
        log.write(str);
        return true;
    } else {
        string str = "Delete All Meeting fail-";
        str += (" User: "+userName);
        log.write(str);
        return false;
    }
}
void AgendaService::startAgenda() {
    storage_ = Storage::getInstance();
}
void AgendaService::quitAgenda() {
    storage_->sync();
}

