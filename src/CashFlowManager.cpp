#include "CashFlowManager.h"
#include <string>
#include <chrono>
#include <iostream>
#include <conio.h>
#include <algorithm>
#include <windows.h>
#include <iomanip>
using namespace std;

CashFlowManager::CashFlowManager(int loggedUserId, string loggedUserFullName, string ifileIncomes, string ifileExpenses)
: fileIncomes(ifileIncomes), fileExpenses(ifileExpenses)
{
    setLoggedUserId(loggedUserId);
    setLoggedUserFullName(loggedUserFullName);
    incomes = fileIncomes.readIncomesFromXML(loggedUserId);
    expenses = fileExpenses.readExpensesFromXML(loggedUserId);
}

string CashFlowManager::getLoggedUserFullName()
{
    return loggedUserFullName;
}

void CashFlowManager::setLoggedUserFullName(string fullName)
{
    loggedUserFullName = fullName;
}

int CashFlowManager::getLoggedUserId()
{
    return loggedUserId;
}

void CashFlowManager::setLoggedUserId(int iloggedUserId)
{
    loggedUserId = iloggedUserId;
}

CashItem CashFlowManager::defineNewCashItem()
{
    string choice;
    string date, name, value;
    cout << "1. Add with today's date" << endl;
    cout << "2. Enter the date manually" << endl << endl;

    do
    {
        cout << "Your choice: ";
        cin.sync();
        getline(cin, choice);
        if ((choice.length() > 1) || (!isdigit(choice[0])))
        {
            choice = "0";
        }

        switch (choice[0])
        {
        case '1':
            date = getCurrentDate();
            break;
        case '2':
            do
            {
                cout << "Please, enter the date in format YYYY-MM-DD: ";
                cin.sync();
                getline(cin, date);
            }
            while (!checkDate(date));
            break;
        default:
            cout << "Invalid input! ";
            break;
        }
    }
    while (choice[0] != '1' && choice[0] != '2');

    cout << "Please, enter a name: ";
    cin.sync();
    getline(cin, name);

    do
    {
        cout << "Please, enter a value separated by dot: ";
        cin.sync();
        getline(cin, value);
    }
    while (!checkCashValue(value));

    cout << "parseCashValue(value): " << parseCashValue(value) << endl;

    CashItem newCashItem(name, date, parseCashValue(value));
    return newCashItem;
}

void CashFlowManager::addIncome()
{
    system("cls");
    cout << "Personal Finance Manager --> User Menu -->  New Income " << endl;
    cout << "Logged as: " << loggedUserFullName << endl << endl;

    CashItem newCashItem = defineNewCashItem();
    Income newIncome(loggedUserId, newCashItem.getName(),
                     newCashItem.getDate(), newCashItem.getValue());

    incomes.push_back(newIncome);
    fileIncomes.addNewItemToXML(newIncome);

    cout << "New income added!";
    Sleep(1000);
}


void CashFlowManager::addExpense()
{
    system("cls");
    cout << "Personal Finance Manager --> User Menu --> New Expense " << endl;
    cout << "Logged as: " << loggedUserFullName << endl << endl;

    CashItem newCashItem = defineNewCashItem();
    Expense newExpense(loggedUserId, newCashItem.getName(),
                     newCashItem.getDate(), newCashItem.getValue());

    expenses.push_back(newExpense);
    fileExpenses.addNewItemToXML(newExpense);

    cout << "New expense added!";
    Sleep(1000);
}

void CashFlowManager::showCompleteBalanceSheet()
{
    int incomesCount = incomes.size();
    int expensesCount = expenses.size();
    incomesSum = 0;
    expensesSum = 0;

    system("cls");
    cout << "Personal Finance Manager --> User Menu --> Complete Balance Sheet " << endl;
    cout << "Logged as: " << loggedUserFullName << endl << endl;

    cout << "Incomes: " << endl;
    for (int i = 0; i < incomesCount; i++)
    {
        incomes[i].printCashItem();
        incomesSum += incomes[i].getValue();
    }

    cout << endl << "Expenses: " << endl;
    for (int i = 0; i < expensesCount; i++)
    {
        expenses[i].printCashItem();
        expensesSum += expenses[i].getValue();
    }

    cout << endl << "Incomes sum: " << incomesSum << endl;
    cout << "Expenses sum: " << expensesSum << endl;
    cout << "Balance: " << incomesSum - expensesSum << endl;

    showReturnMessage();
}

string CashFlowManager::getCurrentDate()
{
    ostringstream osstream;
    string date;
    time_t t = time(0);
    struct tm * now = localtime( & t );
	osstream << (now->tm_year + 1900) << '-'
         << setw(2) << setfill('0') << (now->tm_mon + 1) << '-'
         << setw(2) << setfill('0') << now->tm_mday;
    date = osstream.str();
    return date;
}

int CashFlowManager::getDaysCountForMonth(int month, int year)
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

bool CashFlowManager::checkDate(string date)
{
    if (date.length() != 10)
        return false;

    int i = 0;

    while (i < 10)
    {
        if (i == 4 || i == 7)
        {
            if (date[i] != '-')
            {
                cout << "Invalid format!";
                return false;
            }
        }
        else if (!isdigit(date[i]))
        {
            cout << "Invalid format!";
            return false;
        }
        i++;
    }

    string currentDate = getCurrentDate();
    int year = atoi(date.substr(0,4).c_str());
    int currentYear = atoi(currentDate.substr(0,4).c_str());
    int month = atoi(date.substr(5,2).c_str());
    int currentMonth = atoi(currentDate.substr(5,2).c_str());
    int day = atoi(date.substr(8,2).c_str());

    if ((year > currentYear) || (year < 2000))
    {
        cout << "Invalid year!";
        return false;
    }

    if ((month > 12) || ((year == currentYear) && (month > currentMonth)))
    {
        cout << "Invalid month!";
        return false;
    }

    int monthDaysCount = getDaysCountForMonth(month, year);

    if (day > monthDaysCount)
    {
        cout << "Invalid day!";
        return false;
    }

    return true;
}

bool CashFlowManager::checkCashValue(string &valueString)
{
    int commaCount = 0;
    for (int i = 0; i < valueString.size(); i++)
    {
        if (!isdigit(valueString[i]))
        {
            if (valueString[i] == ',' || valueString[i] == '.')
            {
                if (++commaCount > 1)
                {
                    return false;
                }
            }
            else
                return false;
        }
    }
    return true;
}

float CashFlowManager::parseCashValue(string &valueString)
{
    replace(valueString.begin(), valueString.end(), ',', '.');
    return atof(valueString.c_str());
}


void CashFlowManager::showReturnMessage()
{
    cout << endl << "Press any key to return to User Menu...";
    getch();
}
