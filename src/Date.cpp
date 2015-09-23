#include"Date.h"

int normal[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int special[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// judge whether the year is a “Leap Year”
bool judgeYear(int year) {
    if ((year%4 == 0)&&(year%100 != 0)) {
        return true;
    }
    if (year%400 == 0) {
        return true;
    }
    return false;
}

// judge whether the char is a “Number”
bool isNumber(char n) {
    if ((n >= '0')&&(n <= '9')) return true;
    return false;
}

Date::Date() {
    year_ = 0;
    month_ = 0;
    day_ = 0;
    hour_ = 0;
    minute_ = 0;
}
Date::Date(int y, int m, int d, int h, int mi) {
    year_ = y;
    month_ = m;
    day_ = d;
    hour_ = h;
    minute_ = mi;
}
int Date::getYear() const {
    return year_;
}
void Date::setYear(int year) {
    year_ = year;
}
int Date::getMonth() const {
    return month_;
}
void Date::setMonth(int month) {
    month_ = month;
}
int Date::getDay() const {
    return day_;
}
void Date::setDay(int day) {
    day_ = day;
}
int Date::getHour() const {
    return hour_;
}
void Date::setHour(int hour) {
    hour_ = hour;
}
int Date::getMinute() const {
    return minute_;
}
void Date::setMinute(int minute) {
    minute_ = minute;
}
bool Date::isValid(const Date& date) {
    int hour = date.getHour(), minute = date.getMinute();
    int day = date.getDay(), month = date.getMonth();
    int year = date.getYear();
    if ((hour < 0)||(hour > 23)) return false;
    if ((minute < 0)||(minute > 59))return false;
    if ((month < 0)||(month > 12)) return false;
    if ((year < 1000)||(year > 9999)) return false;
    if (judgeYear(year)) {
        if ((day <= 0)||(day > special[month-1])) {
            return false;
        }
    } else {
        if ((day <= 0)||(day > normal[month-1])) {
            return false;
        }
    }
    return true;
}
Date Date::stringToDate(string str) {
    int len = str.size(), tmp = 0, i = 0;
    Date date;
    while (isNumber(str[i])&&(i < len)) {
        tmp = tmp*10+(str[i]-'0');
        i++;
    }
    date.setYear(tmp);
    tmp = 0;
    i++;
    while (isNumber(str[i])&&(i < len)) {
        tmp = tmp*10+(str[i]-'0');
        i++;
    }
    date.setMonth(tmp);
    tmp = 0;
    i++;
    while (isNumber(str[i])&&(i < len)) {
        tmp = tmp*10+(str[i]-'0');
        i++;
    }
    date.setDay(tmp);
    tmp = 0;
    i++;
    while (isNumber(str[i])&&(i < len)) {
        tmp = tmp*10+(str[i]-'0');
        i++;
    }
    date.setHour(tmp);
    tmp = 0;
    i++;
    while (isNumber(str[i])&&(i < len)) {
        tmp = tmp*10+(str[i]-'0');
        i++;
    }
    date.setMinute(tmp);
    return date;
}
string Date::dateToString(Date date) {
    int y = date.getYear();
    int mo = date.getMonth();
    int d = date.getDay();
    int h = date.getHour();
    int mi = date.getMinute(), i;
    string ans;
    for (i = 1000; i > 0; i /= 10) {
        ans += ((y/i)%10)+'0';
    }
    ans += '-';
    ans += (mo/10)+'0';
    ans += (mo%10)+'0';
    ans += '-';
    ans += (d/10)+'0';
    ans += (d%10)+'0';
    ans += '/';
    ans += (h/10)+'0';
    ans += (h%10)+'0';
    ans += ':';
    ans += (mi/10)+'0';
    ans += (mi%10)+'0';
    return ans;
}
Date& Date::operator=(const Date& date) {
    year_ = date.year_;
    month_ = date.month_;
    day_ = date.day_;
    hour_ = date.hour_;
    minute_ = date.minute_;
    return (*this);
}
bool Date::operator==(const Date& date) const {
    if (year_ != date.year_ ) return false;
    if (month_ != date.month_ ) return false;
    if (day_ != date.day_) return false;
    if (hour_ != date.hour_) return false;
    if (minute_ != date.minute_)  return false;
    return true;
}
bool Date::operator>(const Date& date) const {
    if (year_ < date.year_ ) return false;
    if (year_ > date.year_ ) return true;

    if (month_ < date.month_ ) return false;
    if (month_ > date.month_ ) return true;

    if (day_ < date.day_) return false;
    if (day_ > date.day_) return true;

    if (hour_ < date.hour_) return false;
    if (hour_ > date.hour_) return true;

    if (minute_ < date.minute_)  return false;
    if (minute_ > date.minute_)  return true;

    return false;
}
bool Date::operator<(const Date& date) const {
    if (year_ < date.year_ ) return true;
    if (year_ > date.year_ ) return false;

    if (month_ < date.month_ ) return true;
    if (month_ > date.month_ ) return false;

    if (day_ < date.day_) return true;
    if (day_ > date.day_) return false;

    if (hour_ < date.hour_) return true;
    if (hour_ > date.hour_) return false;

    if (minute_ < date.minute_)  return true;
    if (minute_ > date.minute_)  return false;

    return false;
}
bool Date::operator>=(const Date& date) const {
    if (year_ < date.year_ ) return false;
    if (year_ > date.year_ ) return true;

    if (month_ < date.month_ ) return false;
    if (month_ > date.month_ ) return true;

    if (day_ < date.day_) return false;
    if (day_ > date.day_) return true;

    if (hour_ < date.hour_) return false;
    if (hour_ > date.hour_) return true;

    if (minute_ < date.minute_)  return false;
    if (minute_ > date.minute_)  return true;

    return true;
}
bool Date::operator<=(const Date& date) const {
    if (year_ < date.year_ ) return true;
    if (year_ > date.year_ ) return false;

    if (month_ < date.month_ ) return true;
    if (month_ > date.month_ ) return false;

    if (day_ < date.day_) return true;
    if (day_ > date.day_) return false;

    if (hour_ < date.hour_) return true;
    if (hour_ > date.hour_) return false;

    if (minute_ < date.minute_)  return true;
    if (minute_ > date.minute_)  return false;

    return true;
}

