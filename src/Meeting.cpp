#include"Meeting.h"

Meeting::Meeting() {
    sponsor_ = "";
    participator_ = "";
    startDate_ = Date(0, 0, 0, 0, 0);
    endDate_ = Date(0, 0, 0, 0, 0);
    title_ = "";
}
Meeting::Meeting(string sponsor, string participator,
        Date startTime, Date endTime, string title) {
    sponsor_ = sponsor;
    participator_ = participator;
    startDate_ = startTime;
    endDate_ = endTime;
    title_ = title;
}
string Meeting::getSponsor() const {
    return sponsor_;
}
void Meeting::setSponsor(string sponsor) {
    sponsor_ = sponsor;
}
string Meeting::getParticipator() const {
    return participator_;
}
void Meeting::setParticipator(string participator) {
    participator_ = participator;
}
Date Meeting::getStartDate() const {
    return startDate_;
}
void Meeting::setStartDate(Date startTime) {
    startDate_ = startTime;
}
Date Meeting::getEndDate() const {
    return endDate_;
}
void Meeting::setEndDate(Date endTime) {
    endDate_ = endTime;
}
string Meeting::getTitle() const {
    return title_;
}
void Meeting::setTitle(string title) {
    title_ = title;
}
bool operator<(const Meeting& m1, const Meeting& m2) {
    if (m1.getStartDate() < m2.getStartDate()) return true;
    return false;
}

