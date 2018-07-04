#include "FileUsers.h"
#include <iostream>
#include <windows.h>
using namespace std;

FileUsers::FileUsers(string ifilename)
{
    filename = ifilename;
    loadDataFromXML();
}

void FileUsers::loadDataFromXML()
{
    cout << "Loading data from XML..." << endl;
    xml.Load(filename);
}

void FileUsers::addNewItemToXML(User &newUser)
{
    cout << "Adding new item to XML..." << endl;

    xml.ResetPos();
    if (xml.FindElem("USERS") == false)
        xml.AddElem("USERS");

    xml.IntoElem();
    xml.AddElem("USER");
    xml.IntoElem();
    xml.AddElem("id", conversion.numberToString(newUser.getId()));
    xml.AddElem("name", newUser.getName());
    xml.AddElem("surname", newUser.getSurname());
    xml.AddElem("login", newUser.getLogin());
    xml.AddElem("password", newUser.getPassword());
    xml.OutOfElem();

    xml.Save(filename);
}

void FileUsers::updateXML(vector <User> &users)
{
    cout << "Updating XML..." << endl;

    xml.ResetPos();
    xml.FindElem("USERS");
    xml.RemoveElem();

    if (xml.FindElem("USERS") == false)
        xml.AddElem("USERS");
    xml.IntoElem();

    int usersCount = users.size();
    for (int i = 0; i < usersCount; i++)
    {
        xml.AddElem("USER");
        xml.IntoElem();
        xml.AddElem("id", conversion.numberToString(users[i].getId()));
        xml.AddElem("name", users[i].getName());
        xml.AddElem("surname", users[i].getSurname());
        xml.AddElem("login", users[i].getLogin());
        xml.AddElem("password", users[i].getPassword());
        xml.OutOfElem();
    }
    xml.Save(filename);
}


vector <User> FileUsers::readUsersFromXML()
{
    vector <User> users;
    int id;
    string name, surname, login, password;

    xml.ResetPos();
    if (xml.FindElem("USERS") == true)
    {
        xml.IntoElem();
        while (xml.FindElem("USER"))
        {
            xml.FindChildElem("id");
            id = conversion.string2int(xml.GetChildData());
            xml.FindChildElem("name");
            name = xml.GetChildData();
            xml.FindChildElem("surname");
            surname = xml.GetChildData();
            xml.FindChildElem("login");
            login = xml.GetChildData();
            xml.FindChildElem("password");
            password = xml.GetChildData();
            User newUser(id, name, surname, login, password);
            users.push_back(newUser);
        }
    }
    return users;
}



