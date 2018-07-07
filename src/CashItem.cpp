#include "CashItem.h"
#include <string>
#include <sstream>
#include <iostream>
#include <chrono>
using namespace std;

CashItem::CashItem()
{
    //ctor
}

void CashItem::printCashItem()
{
    cout << getId() << " " << getName() << " " <<
         getValue() << " " << getDate() << endl;
}

int CashItem::getId()
{
    return id;
}

void CashItem::setId(int iid)
{
    id = iid;
}

int CashItem::getUserId()
{
    return userId;
}

void CashItem::setUserId(int iuserId)
{
    userId = iuserId;
}

string CashItem::getName()
{
    return name;
}

void CashItem::setName(string iname)
{
    name = iname;
}


string CashItem::getDate()
{
    return date;
}

void CashItem::setDate(string idate)
{
    date = idate;
}

float CashItem::getValue()
{
    return value;
}

void CashItem::setValue(float ivalue)
{
    value = ivalue;
}

string CashItem::getCurrentDate()
{
    ostringstream osstream;
    string date;
    time_t t = time(0);
    struct tm * now = localtime( & t );
	osstream << (now->tm_year + 1900) << '-'
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday;
    date = osstream.str();
    return date;
}

int CashItem::getMonthDaysCount(int month, int year)
{
    int daysCount = 0;

    switch(month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        daysCount = 31;
        break;
    case 2:
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            daysCount = 29;
        }
        else
        {
            daysCount = 28;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        daysCount = 30;
        break;
    default:
        break;
    }

    return daysCount;
}

bool CashItem::checkDate(string date)
{
    if (date.length() != 10)
        return false;

    int i = 0;

    while (i < 10)
    {
        if (i == 4 || i == 7)
        {
            if (date[i] != '-')
                return false;
        }
        else
        {
            if (!isdigit(date[i]))
                return false;
        }
        i++;
    }

    string currentDate = getCurrentDate();

    cout << date.substr(0,4) << "  " << date.substr(5,2) << "  " << date.substr(8,2) << endl;

    int year = atoi(date.substr(0,4).c_str());
    int currentYear = atoi(currentDate.substr(0,4).c_str());
    int month = atoi(date.substr(5,2).c_str());
    int currentMonth = atoi(currentDate.substr(5,2).c_str());
    int day = atoi(date.substr(8,2).c_str());

    if ((year > currentYear) || (year < 2000))
    {
        cout << "Invalid year!" << endl;
        return false;
    }

    if ((month > 12) || ((year == currentYear) && (month > currentMonth)))
    {
        cout << "Invalid month!" << endl;
        return false;
    }

    int monthDaysCount = getMonthDaysCount(month, year);

    cout << "monthDaysCount = " << monthDaysCount << endl;

    if (day > monthDaysCount)
    {
        cout << "Invalid day!" << endl;
        return false;
    }

    return true;
}


float CashItem::parseCashValue(string valueString)
{
    return 1.1;
}





