#include"AgendaUI.h"
#include<iostream>
#include<string>
#include<iomanip>
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::left;
using std::setw;

void AgendaUI::OperationLoop() {
    flat = true;
    startAgenda();
    while (flat) {
        executeOperation(getOperation());
    }
}
AgendaUI::AgendaUI() {
    userName_ = "";
    userPassword_ = "";
}

void printMenuo() {
    cout << "----------------------- Agenda ------------------------------\n"
         << "Action :                                                     \n"
         << "l   - log in Agenda by ueser name and password               \n"
         << "r   - register an Agenda account                             \n"
         << "q   - quit Agenda                                            \n"
         << "rU  - reload a User                                          \n"
         << "-------------------------------------------------------------\n"
         << endl;
}
void printMenul() {
    cout << "----------------------- Agenda ------------------------------\n"
         << "Action :                                                     \n"
         << "o    - log out Agenda                                        \n"
         << "dc   - delete Agenda account                                 \n"
         << "lu   - list all Agenda user                                  \n"
         << "cm   - create a meeting                                      \n"
         << "la   - list all meetings                                     \n"
         << "las  - list all sponsor meetings                             \n"
         << "lap  - list all participate meetings                         \n"
         << "qm   - query meeting by title                                \n"
         << "qt   - query meeting by time interval                        \n"
         << "dm   - delete meeting by title                               \n"
         << "da   - delete all meetings                                   \n"
         << "rM   - reload meetings                                       \n"
         << "-------------------------------------------------------------\n"
         << endl;
}

void AgendaUI::startAgenda() {
    cout << endl;
    agendaService_.startAgenda();
    printMenuo();
}
string AgendaUI::getOperation() {
    if (userName_ == "") {
        string operation;
        cout << "Agenda : ~$ ";
        cin >> operation;
        return operation;
    } else {
        string operation;
        cout << "Agenda@" << userName_ << " : ~# ";
        cin >> operation;
        return operation;
    }
}
bool AgendaUI::executeOperation(std::string op) {
    cout << endl;
    if (userName_ == "") {
        if (op == "l") {
            userLogIn();
        }
        if (op == "r") {
            userRegister();
        }
        if (op == "q") {
            quitAgenda();
        }
        if (op == "rU") {
            reloadUser();
        }
    } else {
        if (op == "o") {
            userLogOut();
        }
        if (op == "dc") {
            deleteUser();
        }
        if (op == "lu") {
            listAllUsers();
        }
        if (op == "cm") {
            createMeeting();
        }
        if (op == "la") {
            listAllMeetings();
        }
        if (op == "las") {
            listAllSponsorMeetings();
        }
        if (op == "lap") {
            listAllParticipateMeetings();
        }
        if (op == "qm") {
            queryMeetingByTitle();
        }
        if (op == "qt") {
            queryMeetingByTimeInterval();
        }
        if (op == "dm") {
            deleteMeetingByTitle();
        }
        if (op == "da") {
            deleteAllMeetings();
        }
        if (op == "rM") {
            reloadMeetings();
        }
    }
    if (op != "q") {
        if ((userName_ == "")) {
            printMenuo();
        } else {
            printMenul();
        }
    }
}
void AgendaUI::reloadUser() {
    string time, userName;
    cout << "[reload User] [time(yyyy-mm-dd/hh:mm:ss)] [userName]" << endl;
    cout << "[reload User] ";
    cin >> time >> userName;
    if (agendaService_.reloadUser(time, userName)) {
        cout << "[reload User] succeed!" << endl << endl;
    } else {
        cout << "[error] reload fail!" << endl << endl;
    }
}
void AgendaUI::reloadMeetings() {
    string time, userName;
    cout << "[reload Meetings] [time(yyyy-mm-dd/hh:mm:ss)]" << endl;
    cout << "[reload Meetings] ";
    cin >> time;
    if (agendaService_.reloadMeeting(time, userName_)) {
        cout << "[reload Meetings] succeed!" << endl << endl;
    } else {
        cout << "[error] reload fail!" << endl << endl;
    }
}
void AgendaUI::userLogIn() {
    string username, password;
    cout << "[log in] [user name] [password]" << endl;
    cout << "[log in] ";
    cin >> username >> password;
    if (agendaService_.userLogIn(username, password)) {
        cout << "[log in] succeed!" << endl << endl;
        userName_ = username;
        userPassword_ = password;
    } else {
        cout << "[error] log in fail!" << endl << endl;
    }
}
void AgendaUI::userRegister() {
    string username, password, email, phone;
    cout << "[register] [user name] [password] [email] [phone]" << endl;
    cout << "[register] ";
    cin >> username >> password >> email >> phone;
    if (agendaService_.userRegister(username, password, email, phone)) {
        cout << "[register] succeed!" << endl << endl;
    } else {
        cout << "[error] register fail!" << endl << endl;
    }
}
void AgendaUI::quitAgenda() {
    cout << "Switching off......" << endl << endl;
    agendaService_.quitAgenda();
    flat = false;
} 
void AgendaUI::userLogOut() {
    userName_ = "";
    userPassword_ = "";
}
void AgendaUI::deleteUser() {
    if (agendaService_.deleteUser(userName_, userPassword_)) {
        userLogOut();
        cout << "[delete agenda account] succeed!" << endl << endl;
    } else {
        cout << "[error] delete agenda account fail!" << endl << endl;
    }
}
void AgendaUI::listAllUsers() {
    cout << "[list all users]\n" << endl;
    cout << left << setw(15) << "name";
    cout << left << setw(20) << "email";
    cout << "phone" << endl;
    list<User> U = agendaService_.listAllUsers();
    list<User>::iterator it = U.begin();
    while (it != U.end()) {
        cout << left << setw(15) << it->getName();
        cout << left << setw(20) << it->getEmail();
        cout << it->getPhone() << endl;
        it++;
    }
    cout << endl;
}
void AgendaUI::createMeeting() {
    string title, participator, sdate, edate;
    cout << "[create meeting] [title] [participator] ";
    cout << "[start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
    cout << "[create meeting] ";
    cin >> title >> participator >> sdate >> edate;
    if (agendaService_.createMeeting(userName_, title, participator, sdate, edate)) {
        cout << "[create meeting] succeed!" << endl << endl;
    } else {
        cout << "[error] create meeting fail!" << endl << endl;
    }
}
void AgendaUI::listAllMeetings() {
    cout << "[list all meeting]\n" << endl;
    list<Meeting> M = agendaService_.listAllMeetings(userName_);
    printMeetings(M);
}
void AgendaUI::listAllSponsorMeetings() {
    cout << "[list all sponsor meeting]\n" << endl;
    list<Meeting> M = agendaService_.listAllSponsorMeetings(userName_);
    printMeetings(M);
}
void AgendaUI::listAllParticipateMeetings() {
    cout << "[list all participate meeting]\n" << endl;
    list<Meeting> M = agendaService_.listAllParticipateMeetings(userName_);
    printMeetings(M);
}
void AgendaUI::queryMeetingByTitle() {
    string title;
    cout << "[query meeting] [title]" << endl;
    cout << "[query meeting] ";
    cin >> title;
    cout << endl;
    list<Meeting> M = agendaService_.meetingQuery(userName_, title);
    printMeetings(M);
}
void AgendaUI::queryMeetingByTimeInterval() {
    string sdate, edate;
    cout << "[query meetings] ";
    cout << "[start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
    cout << "[query meetings] ";
    cin >> sdate >> edate;
    cout << endl << "[query meetings]" << endl;
    list<Meeting> M = agendaService_.meetingQuery(userName_, sdate, edate);
    printMeetings(M);
}
void AgendaUI::deleteMeetingByTitle() {
    string title;
    cout << "[delete meeting by title] [title]" << endl;
    cout << "[delete meeting by title] ";
    cin >> title;
    cout << endl;
    if (agendaService_.deleteMeeting(userName_, title)) {
        cout << "[delete meeting by title] succeed!" << endl << endl;
    } else {
        cout << "[error] delete meeting fail!" << endl << endl;
    }
}
void AgendaUI::deleteAllMeetings() {
    if (agendaService_.deleteAllMeetings(userName_)) {
        cout << "[delete all meetings] succeed!" << endl << endl;
    } else {
        cout << "[error] delete all meetings fail!" << endl << endl;
    }
}
void AgendaUI::printMeetings(list<Meeting> meetings) {
    cout << left << setw(15) << "title";
    cout << left << setw(14) << "sponsor";
    cout << left << setw(14) << "participator";
    cout << left << setw(20) << "start time";
    cout << "end time" << endl;
    list<Meeting>::iterator it = meetings.begin();
    while (it != meetings.end()) {
        cout << left << setw(15) << it->getTitle();
        cout << left << setw(14) << it->getSponsor();
        cout << left << setw(14) << it->getParticipator();
        cout << left << setw(20) << Date::dateToString(it->getStartDate());
        cout << Date::dateToString(it->getEndDate()) << endl;
        it++;
    }
    cout << endl;
}

