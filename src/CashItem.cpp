#include "CashItem.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

CashItem::CashItem()
{
    //ctor
}

CashItem::CashItem(string name, string date, float value)
{
    setName(name);
    setDate(date);
    setValue(value);
}

void CashItem::printCashItem()
{
    cout << setw(4) << getId() << setw(30) << getName() << setw(14) <<
         fixed << setprecision(2) << getValue() << setw(16) << getDate() << endl;
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






