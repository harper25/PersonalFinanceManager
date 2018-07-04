#include "User.h"
using namespace std;

int User::nextId = 1;

User::User(string name, string surname, string login, string password)
{
    setId(nextId++);
    setName(name);
    setSurname(surname);
    setLogin(login);
    setPassword(password);
}

User::User(int id, string name, string surname, string login, string password)
{
    setId(id);
    if (id >= nextId)
        nextId = id + 1;
    setName(name);
    setSurname(surname);
    setLogin(login);
    setPassword(password);
}

string User::getName()
{
    return name;
}

void User::setName(string iname)
{
    name = iname;
}

string User::getSurname()
{
    return surname;
}

void User::setSurname(string isurname)
{
    surname = isurname;
}

string User::getLogin()
{
    return login;
}

void User::setLogin(string ilogin)
{
    login = ilogin;
}

string User::getPassword()
{
    return password;
}

void User::setPassword(string ipassword)
{
    password = ipassword;
}

int User::getNextId()
{
    return nextId;
}

void User::setId(int iid)
{
    id = iid;
}

int User::getId()
{
    return id;
}


