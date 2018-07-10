#include "FileExpenses.h"
#include <iostream>
#include <windows.h>
using namespace std;

FileExpenses::FileExpenses(string ifilename)
{
    filename = ifilename;
    loadDataFromXML();
}

void FileExpenses::loadDataFromXML()
{
    xml.Load(filename);
}

void FileExpenses::addNewItemToXML(Expense &newExpense)
{
    xml.ResetPos();
    if (xml.FindElem("EXPENSES") == false)
        xml.AddElem("EXPENSES");

    xml.IntoElem();
    xml.AddElem("EXPENSE");
    xml.IntoElem();
    xml.AddElem("id", conversion.numberToString(newExpense.getId()));
    xml.AddElem("userId", conversion.numberToString(newExpense.getUserId()));
    xml.AddElem("name", newExpense.getName());
    xml.AddElem("date", newExpense.getDate());
    xml.AddElem("value", conversion.numberToString(newExpense.getValue()));
    xml.OutOfElem();
    xml.Save(filename);
}


void FileExpenses::updateXML(vector <Expense> &expenses)
{
    cout << "Updating XML..." << endl;
}


vector <Expense> FileExpenses::readExpensesFromXML(int loggedUserId)
{
    vector <Expense> expenses;
    int id, userId;
    string name, date;
    double value;

    xml.ResetPos();
    if (xml.FindElem("EXPENSES") == true)
    {
        xml.IntoElem();
        while (xml.FindElem("EXPENSE"))
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
            Expense newExpense(id, userId, name, date, value);

            if (userId == loggedUserId)
            {
                expenses.push_back(newExpense);
            }
        }
    }
    return expenses;
}

