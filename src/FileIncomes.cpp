#include "FileIncomes.h"
#include <iostream>
#include <windows.h>
using namespace std;

FileIncomes::FileIncomes(string ifilename)
{
    filename = ifilename;
    loadDataFromXML();
}

void FileIncomes::loadDataFromXML()
{
    xml.Load(filename);
}

void FileIncomes::addNewItemToXML(Income &newIncome)
{
    xml.ResetPos();
    if (xml.FindElem("INCOMES") == false)
        xml.AddElem("INCOMES");

    xml.IntoElem();
    xml.AddElem("INCOME");
    xml.IntoElem();
    xml.AddElem("id", conversion.numberToString(newIncome.getId()));
    xml.AddElem("userId", conversion.numberToString(newIncome.getUserId()));
    xml.AddElem("name", newIncome.getName());
    xml.AddElem("date", newIncome.getDate());
    xml.AddElem("value", conversion.numberToString(newIncome.getValue()));
    xml.OutOfElem();
    xml.Save(filename);
}

void FileIncomes::updateXML(vector <Income> &incomes)
{
    cout << "Updating XML..." << endl;
}

vector <Income> FileIncomes::readIncomesFromXML(int loggedUserId)
{
    vector <Income> incomes;
    int id, userId;
    string name, date;
    double value;

    xml.ResetPos();
    if (xml.FindElem("INCOMES") == true)
    {
        xml.IntoElem();
        while (xml.FindElem("INCOME"))
        {
            xml.FindChildElem("id");
            id = conversion.string2int(xml.GetChildData());
            xml.FindChildElem("userId");
            userId = conversion.string2int(xml.GetChildData());
            xml.FindChildElem("name");
            name = xml.GetChildData();
            xml.FindChildElem("date");
            date = xml.GetChildData();
            xml.FindChildElem("value");
            value = conversion.string2double(xml.GetChildData());
            Income newIncome(id, userId, name, date, value);
            if (userId == loggedUserId)
            {
                incomes.push_back(newIncome);
            }
        }
    }
    return incomes;
}

