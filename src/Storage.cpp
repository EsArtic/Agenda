#include"Storage.h"
#include<fstream>
#include<iostream>
using std::ifstream;
using std::ofstream;
using std::endl;

Storage* Storage::instance_ = NULL;
// singleton
Storage* Storage::getInstance() {
    if (instance_ != NULL) {
        return instance_;
    } else {
        instance_ = new Storage();
        return instance_;
    }
}
Storage::Storage() {
    if (readFromFile("agenda.data")) {
    } else {
        readFromFile("sync/back-up.data");
    }
}
Storage::~Storage() {
    writeToFile("agenda.data");
    writeToFile("sync/back-up.data");
    instance_ = NULL;
}
// CRUD for User & Meeting
// using C++11 Function Template and Lambda Expressions
void Storage::createUser(const User& U) {
    userList_.push_back(U);
}
list<User> Storage::queryUser(function<bool(const User&)> filter) {
    list<User>::iterator it = userList_.begin();
    list<User> ans;
    while (it != userList_.end()) {
        if (filter(*it)) {
            ans.push_back(*it);
        }
        it++;
    }
    return ans;
}
// return found users

int Storage::updateUser(function<bool(const User&)> filter,
               function<void(User&)> switcher) {
    list<User>::iterator it = userList_.begin();
    int ans = 0;
    while (it != userList_.end()) {
        if (filter(*it)) {
            switcher(*it);
            ans++;
        }
        it++;
    }
    return ans;
}
// return the number of updated users
list<User> Storage::deleteUser(function<bool(const User&)> filter) {
    list<User>::iterator it = userList_.begin();
    list<User> ans;
    while (it != userList_.end()) {
        if (filter(*it)) {
            ans.push_back(*it);
            userList_.erase(it++);
            it++;
        } else {
            it++;
        }
    }
    return ans;
}
// return the number of deleted users
void Storage::createMeeting(const Meeting& M) {
    meetingList_.push_back(M);
}
list<Meeting> Storage::queryMeeting(function<bool(const Meeting&)> filter) {
    list<Meeting>::iterator it = meetingList_.begin();
    list<Meeting> ans;
    while (it != meetingList_.end()) {
        if (filter(*it)) {
            ans.push_back(*it);
        }
        it++;
    }
    return ans;
}
// return found meetings
int Storage::updateMeeting(function<bool(const Meeting&)>filter,
                  function<void(Meeting&)> switcher) {
    list<Meeting>::iterator it = meetingList_.begin();
    int ans = 0;
    while (it != meetingList_.end()) {
        if (filter(*it)) {
            switcher(*it);
            ans++;
        }
        it++;
    }
    return ans;
}
// return the number of updated meetings
list<Meeting> Storage::deleteMeeting(std::function<bool(const Meeting&)> filter) {
    list<Meeting>::iterator it = meetingList_.begin();
    list<Meeting> ans;
    while (it != meetingList_.end()) {
        if (filter(*it)) {
            ans.push_back(*it);
            meetingList_.erase(it++);
            it++;
        } else {
            it++;
        }
    }
    return ans;
}
// return the number of deleted meetings
// File IO
bool Storage::sync() {
    return writeToFile("agenda.data");
}
bool Storage::readFromFile(const char *fpath) {
    ifstream in(fpath);
    if (!in) return false;

    string tmp;
    string name, password, email, phone;
    string sponsor, participator, sdate, edate, title;
    Date Sdate, Edate;
    int i, j, num;

    while (!in.eof()) {
        num = 0;
        getline(in, tmp);
        int l = tmp.size();
        if (tmp.find("User") != string::npos) {
            for (i = 0; i < l; i++) {
                if ((tmp[i] >= '0')&&(tmp[i] <= '9')) {
                    j = i;
                    while ((tmp[j] >= '0')&&(tmp[j] <= '9')) {
                        num = num*10+(tmp[j]-'0');
                        j++;
                    }
                    break;
                }
            }
            i = 0;
            size_t pos;
            while (i < num) {
                getline(in, tmp);
                pos = tmp.find("name");
                pos += 6;
                while (tmp[pos] != '"') {
                    name += tmp[pos];
                    pos++;
                }
                pos = tmp.find("password");
                pos += 10;
                while (tmp[pos] != '"') {
                    password += tmp[pos];
                    pos++;
                }
                pos = tmp.find("email");
                pos += 7;
                while (tmp[pos] != '"') {
                    email += tmp[pos];
                    pos++;
                }
                pos = tmp.find("phone");
                pos += 7;
                while (tmp[pos] != '"') {
                    phone += tmp[pos];
                    pos++;
                }
                userList_.push_back(User(name, password, email, phone));
                name.clear();
                password.clear();
                email.clear();
                phone.clear();
                i++;
            }
        } else {
            for (i = 0; i < l; i++) {
                if ((tmp[i] >= '0')&&(tmp[i] <= '9')) {
                    j = i;
                    while ((tmp[j] >= '0')&&(tmp[j] <= '9')) {
                        num = num*10+(tmp[j]-'0');
                        j++;
                    }
                    break;
                }
            }
            i = 0;
            size_t pos;
            while (i < num) {
                getline(in, tmp);
                pos = tmp.find("sponsor");
                pos += 9;
                while (tmp[pos] != '"') {
                    sponsor += tmp[pos];
                    pos++;
                }
                pos = tmp.find("participator");
                pos += 14;
                while (tmp[pos] != '"') {
                    participator += tmp[pos];
                    pos++;
                }
                pos = tmp.find("sdate");
                pos += 7;
                while (tmp[pos] != '"') {
                    sdate += tmp[pos];
                    pos++;
                }
                pos = tmp.find("edate");
                pos += 7;
                while (tmp[pos] != '"') {
                    edate += tmp[pos];
                    pos++;
                }
                pos = tmp.find("title");
                pos += 7;
                while (tmp[pos] != '"') {
                    title += tmp[pos];
                    pos++;
                }
                Sdate = Date::stringToDate(sdate);
                Edate = Date::stringToDate(edate);
                meetingList_.push_back(Meeting(sponsor, participator,
                                               Sdate, Edate, title));
                sponsor.clear();
                participator.clear();
                sdate.clear();
                edate.clear();
                title.clear();
                i++;
            }
        }
    }
    in.close();
    userList_.sort();
    meetingList_.sort();
    return true;
}
bool Storage::writeToFile(const char *fpath) {
    ofstream out(fpath);
    if (!out) return false;

    userList_.sort();
    meetingList_.sort();

    out << "{collection:\"User\",total:" << userList_.size() << "}" << endl;
    list<User>::iterator ut = userList_.begin();
    while (ut != userList_.end()) {
        out << "{name:\"" << ut->getName();
        out << "\",password:\"" << ut->getPassword();
        out << "\",email:\"" << ut->getEmail();
        out << "\",phone:\"" << ut->getPhone() << "\"}" << endl;
        ut++;
    }
    out << "{collection:\"Meeting\",total:";
    out << meetingList_.size() << "}" << endl;
    list<Meeting>::iterator mt = meetingList_.begin();
    while (mt != meetingList_.end()) {
        out << "{sponsor:\"" << mt->getSponsor();
        out << "\",participator:\"" << mt->getParticipator();
        out << "\",sdate:\"" << Date::dateToString(mt->getStartDate());
        out << "\",edate:\"" << Date::dateToString(mt->getEndDate());
        out << "\",title:\"" << mt->getTitle() << "\"}" << endl;
        mt++;
    }
    out.close();
    return true;
}

