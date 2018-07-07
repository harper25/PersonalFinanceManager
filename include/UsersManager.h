#ifndef USERSMANAGER_H
#define USERSMANAGER_H

#include "User.h"
#include "FileUsers.h"
#include <vector>

class UsersManager
{
    public:
        UsersManager(std::string = "fileUsers.xml");
        void registerNewUser();
        void logging();
        void changePassword();
        int getLoggedUserId();
        void setLoggedUserId(int);

        std::string getLoggedUserFullName();
        void setLoggedUserFullName(std::string = "");

    protected:

    private:
        std::vector <User> users;
        FileUsers fileUsers;
        int loggedUserId;
        std::string loggedUserFullName;
};

#endif // USERSMANAGER_H
