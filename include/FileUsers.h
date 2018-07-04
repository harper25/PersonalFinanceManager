#ifndef FILEUSERS_H
#define FILEUSERS_H

#include <File.h>
#include "User.h"
#include <string>
#include <vector>


class FileUsers : public File
{
    public:
        FileUsers(std::string);

        void loadDataFromXML();
        void addNewItemToXML(User &newUser);
        void updateXML(std::vector <User> &users);

        std::vector <User> readUsersFromXML();

    protected:
    private:
};

#endif // FILEUSERS_H
