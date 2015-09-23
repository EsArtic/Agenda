#ifndef USER_H
#define USER_H
#include <string>
using std::string;

class User {
    public:
        User();
        User(string userName, string userPassword,
        string userEmail, string userPhone);
        string getName() const;
        void setName(string name);
        string getPassword() const;
        void setPassword(string password);
        string getEmail() const;
        void setEmail(string email);
        string getPhone() const;
        void setPhone(string phone);
        friend bool operator < (const User& u1, const User& u2);
    private:
        string name_;
        string password_;
        string email_;
        string phone_;
};

#endif
