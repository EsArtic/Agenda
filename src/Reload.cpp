#include"Reload.h"
#include<fstream>
#include<iostream>
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;

Reload* Reload::instance_ = NULL;
Reload* Reload::getInstance() {
    if (instance_ == NULL)
        instance_ = new Reload;
    return instance_;
}
Reload::~Reload() {
    writeToFile("sync/User.data", "sync/Meeting.data");
    instance_ = NULL;
}
bool Reload::reloadUser(string date, string username, Storage* storage_) {
    map<string, User>::iterator it = userM.begin();
    int num = 0;
    while (it != userM.end()) {
        if (it->first >= date) {
            if (it->second.getName() == username) {
                storage_->createUser(it->second);
                num++;
            }
        }
        it++;
    }
    if (num) {
        return true;
    } else {
        return false;
    }
}

bool Reload::reloadMeeting(string date, string username, Storage* storage_) {
    map<string, Meeting>::iterator it = meetingM.begin();
    int num = 0, error;
    while (it != meetingM.end()) {
        if (it->first >= date) {
            if (it->second.getSponsor() == username) {
                error = 1;
                list<Meeting> m1 = storage_->queryMeeting([&](Meeting M)->bool {
                    if (M.getSponsor() == username) return true;
                    if (M.getParticipator() == username) return true;
                    return false;});
                list<Meeting>::iterator mt = m1.begin();
                while (mt != m1.end()) {
                    if (!((mt->getEndDate() <= it->second.getStartDate())||
                          (mt->getStartDate() >= it->second.getEndDate()))) {
                        error++;
                    }
                    if (mt->getTitle() == it->second.getTitle()) error++;
                    mt++;
                }
                if (error > 1) {
                    it++;
                    continue;
                }

                error = 1;
                list<Meeting> m2 = storage_->queryMeeting([&](Meeting M)->bool {
                    if (M.getSponsor() == it->second.getParticipator()) return true;
                    if (M.getParticipator() == it->second.getParticipator()) return true;
                    return false;});
                mt = m2.begin();
                while (mt != m2.end()) {
                    if (!((mt->getEndDate() <= it->second.getStartDate())||
                          (mt->getStartDate() >= it->second.getEndDate()))) {
                        error++;
                    }
                    if (mt->getTitle() == it->second.getTitle()) error++;
                    mt++;
                }
                if (error > 1) {
                    it++;
                    continue;
                }

                storage_->createMeeting(it->second);
                num++;
            }
        }
        it++;
    }
    if (num) {
        return true;
    } else {
        return false;
    }
}

bool Reload::readFromFile(const char *Ufpath, const char *Mfpath) {
    ifstream in1(Ufpath);
    ifstream in2(Mfpath);
    if (!in1) return false;
    if (!in2) return false;

    string tmp, time;
    string name, password, email, phone;
    string sponsor, participator, sdate, edate, title;
    Date Sdate, Edate;

    size_t pos;
    while (!in1.eof()) {
        getline(in1, tmp);
        pos = tmp.find("time");
        if (pos == string::npos) break;
        pos += 6;
        while (tmp[pos] != '"') {
            time += tmp[pos];
            pos++;
        }
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
        userM[time] = User(name, password, email, phone);
        name.clear();
        password.clear();
        email.clear();
        phone.clear();
        time.clear();
    }
    while (!in2.eof()) {
        getline(in2, tmp);
        pos = tmp.find("time");
        if (pos == string::npos) break;
        pos += 6;
        while (tmp[pos] != '"') {
            time += tmp[pos];
            pos++;
        }
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
        meetingM[time] = Meeting(sponsor, participator,
                                 Sdate, Edate, title);
        sponsor.clear();
        participator.clear();
        sdate.clear();
        edate.clear();
        title.clear();
        time.clear();
    }
    in1.close();
    in2.close();
    return true;
}

bool Reload::writeToFile(const char *Nfpath, const char *Mfpath) {
    ofstream out1(Nfpath);
    ofstream out2(Mfpath);
    if (!out1) return false;
    if (!out2) return false;

    map<string, User>::iterator ut = userM.begin();
    while (ut != userM.end()) {
        out1 << "{time:\"" << ut->first;
        out1 << "\",name:\"" << ut->second.getName();
        out1 << "\",password:\"" << ut->second.getPassword();
        out1 << "\",email:\"" << ut->second.getEmail();
        out1 << "\",phone:\"" << ut->second.getPhone() << "\"}" << endl;
        ut++;
    }

    map<string, Meeting>::iterator mt = meetingM.begin();
    while (mt != meetingM.end()) {
        out2 << "{time:\"" << mt->first;
        out2 << "\",sponsor:\"" << mt->second.getSponsor();
        out2 << "\",participator:\"" << mt->second.getParticipator();
        out2 << "\",sdate:\"" << Date::dateToString(mt->second.getStartDate());
        out2 << "\",edate:\"" << Date::dateToString(mt->second.getEndDate());
        out2 << "\",title:\"" << mt->second.getTitle() << "\"}" << endl;
        mt++;
    }
    out1.close();
    out2.close();
    return true;
}


void Reload::write(User U) {
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
    userM[key] = U;
}
void Reload::write(Meeting M) {
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
    meetingM[key] = M;
}
Reload::Reload() {
    readFromFile("sync/User.data", "sync/Meeting.data");
}

