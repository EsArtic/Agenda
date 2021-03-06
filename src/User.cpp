#include"User.h"

User::User() {
    name_ = "";
    password_ = "";
    email_ = "";
    phone_ = "";
}
User::User(string userName, string userPassword,
           string userEmail, string userPhone) {
    name_ = userName;
    password_ = userPassword;
    email_ = userEmail;
    phone_ = userPhone;
}
string User::getName() const {
    return name_;
}
void User::setName(string name) {
    name_ = name;
}
string User::getPassword() const {
    return password_;
}
void User::setPassword(string password) {
    password_ = password;
}
string User::getEmail() const {
    return email_;
}
void User::setEmail(string email) {
    email_ = email;
}
string User::getPhone() const {
    return phone_;
}
void User::setPhone(string phone) {
    phone_ = phone;
}
bool operator < (const User& u1, const User& u2) {
    if (u1.getName() < u2.getName()) return true;
    return false;
}

