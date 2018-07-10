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
    indicesOfMatchingIncomes.clear();
    indicesOfMatchingExpenses.clear();

    for (int i = 0; i < incomesCount; i++)
        indicesOfMatchingIncomes.push_back(i);
    for (int i = 0; i < expensesCount; i++)
        indicesOfMatchingExpenses.push_back(i);

    system("cls");
    cout << "Personal Finance Manager --> User Menu --> Complete Balance Sheet " << endl;
    cout << "Logged as: " << loggedUserFullName << endl << endl;

    showSelectedCashItems();
}

void CashFlowManager::showSelectedCashItems()
{
    if (indicesOfMatchingIncomes.size() == 0 && indicesOfMatchingExpenses.size() == 0)
    {
        cout << "There is no incomes nor expenses in this period! " << endl;
        Sleep(1000);
        return;
    }

    if (indicesOfMatchingExpenses.size() > 1)
        quicksortIncomes(0, indicesOfMatchingIncomes.size() - 1);
    if (indicesOfMatchingExpenses.size() > 1)
        quicksortExpenses(0, indicesOfMatchingExpenses.size() - 1);

    cout << "Incomes: " << endl;
    for (int i = 0; i < indicesOfMatchingIncomes.size(); i++)
    {
        cout << setw(4) << i+1;
        incomes[indicesOfMatchingIncomes[i]].printCashItem();
        incomesSum += incomes[indicesOfMatchingIncomes[i]].getValue();
    }

    cout << endl << "Expenses: " << endl;
    for (int i = 0; i < indicesOfMatchingExpenses.size(); i++)
    {
        cout << setw(4) << i+1;
        expenses[indicesOfMatchingExpenses[i]].printCashItem();
        expensesSum += expenses[indicesOfMatchingExpenses[i]].getValue();
    }

    cout << endl << "Incomes sum: " << setw(12) << incomesSum << endl;
    cout << "Expenses sum: " << setw(11) << expensesSum << endl;
    cout << "Balance: " << setw(16) << incomesSum - expensesSum << endl;

    showReturnMessage();
}

void CashFlowManager::showCurrentMonthBalanceSheet()
{
    indicesOfMatchingIncomes.clear();
    indicesOfMatchingExpenses.clear();
    int allIncomesCount = incomes.size();
    int allExpensesCount = expenses.size();
    incomesSum = 0;
    expensesSum = 0;

    string currentMonth = getCurrentDate().substr(5,2);

    for (int i = 0; i < allIncomesCount; i++)
    {
        if (currentMonth == incomes[i].getDate().substr(5,2))
            indicesOfMatchingIncomes.push_back(i);
    }

    for (int i = 0; i < allExpensesCount; i++)
    {
        if (currentMonth == expenses[i].getDate().substr(5,2))
            indicesOfMatchingExpenses.push_back(i);
    }

    system("cls");
    cout << "Personal Finance Manager --> User Menu --> Current Month Balance Sheet " << endl;
    cout << "Logged as: " << loggedUserFullName << endl << endl;

    showSelectedCashItems();
}

void CashFlowManager::showPreviousMonthBalanceSheet()
{
    indicesOfMatchingIncomes.clear();
    indicesOfMatchingExpenses.clear();
    int allIncomesCount = incomes.size();
    int allExpensesCount = expenses.size();
    incomesSum = 0;
    expensesSum = 0;

    int currentMonth = atoi(getCurrentDate().substr(5,2).c_str());

    for (int i = 0; i < allIncomesCount; i++)
    {
        if (currentMonth - 1 == atoi(incomes[i].getDate().substr(5,2).c_str()))
            indicesOfMatchingIncomes.push_back(i);
    }

    for (int i = 0; i < allExpensesCount; i++)
    {
        if (currentMonth - 1 == atoi(expenses[i].getDate().substr(5,2).c_str()))
            indicesOfMatchingExpenses.push_back(i);
    }

    system("cls");
    cout << "Personal Finance Manager --> User Menu --> Previous Month Balance Sheet " << endl;
    cout << "Logged as: " << loggedUserFullName << endl << endl;

    showSelectedCashItems();
}


void CashFlowManager::showBalanceSheetForSelectedPeriod()
{
    system("cls");
    cout << "Personal Finance Manager --> User Menu --> Balance Sheet For Selected Period of Time" << endl;
    cout << "Logged as: " << loggedUserFullName << endl << endl;

    string startDate, endDate;
    indicesOfMatchingIncomes.clear();
    indicesOfMatchingExpenses.clear();
    int allIncomesCount = incomes.size();
    int allExpensesCount = expenses.size();
    incomesSum = 0;
    expensesSum = 0;

    do
    {
        cout << "Please, enter the start date in format YYYY-MM-DD: ";
        cin.sync();
        getline(cin, startDate);
    }
    while (!checkDate(startDate));

    do
    {
        cout << "Please, enter the end date in format YYYY-MM-DD: ";
        cin.sync();
        getline(cin, endDate);
    }
    while (!checkDate(endDate));

    cout << endl;

    if (startDate > endDate)
    {
        cout << "Invalid period of time!" << endl;
        Sleep(1000);
        return;
    }

    for (int i = 0; i < allIncomesCount; i++)
    {
        if (incomes[i].getDate() >= startDate && incomes[i].getDate() <= endDate)
            indicesOfMatchingIncomes.push_back(i);
    }

    for (int i = 0; i < allExpensesCount; i++)
    {
        if (expenses[i].getDate() >= startDate && expenses[i].getDate() <= endDate)
            indicesOfMatchingExpenses.push_back(i);
    }

    showSelectedCashItems();
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

double CashFlowManager::parseCashValue(string &valueString)
{
    replace(valueString.begin(), valueString.end(), ',', '.');
    double valueDouble = atof(valueString.c_str());
    return valueDouble;
}

void CashFlowManager::clearSettings()
{
    incomes.clear();
    expenses.clear();
    indicesOfMatchingIncomes.clear();
    indicesOfMatchingExpenses.clear();
    setLoggedUserId(0);
    setLoggedUserFullName();
}

void CashFlowManager::showReturnMessage()
{
    cout << endl << "Press any key to return to User Menu...";
    getch();
}


void CashFlowManager::quicksortIncomes(int left, int right)
{
    string v = incomes[indicesOfMatchingIncomes[(left + right)/2]].getDate();
    int i, j, buffer;
    i = left;
    j = right;

    do
    {
            while(incomes[indicesOfMatchingIncomes[i]].getDate() < v)
                i++;
            while(incomes[indicesOfMatchingIncomes[j]].getDate() > v)
                j--;

            if(i <= j)
            {
                buffer = indicesOfMatchingIncomes[i];
                indicesOfMatchingIncomes[i] = indicesOfMatchingIncomes[j];
                indicesOfMatchingIncomes[j] = buffer;
                i++;
                j--;
            }
    }
    while(i <= j);

    if(j > left)
            quicksortIncomes(left, j);
    if(i < right)
            quicksortIncomes(i, right);
}


void CashFlowManager::quicksortExpenses(int left, int right)
{
    string v = expenses[indicesOfMatchingExpenses[(left + right)/2]].getDate();
    int i, j, buffer;
    i = left;
    j = right;

    do
    {
            while(expenses[indicesOfMatchingExpenses[i]].getDate() < v)
                i++;
            while(expenses[indicesOfMatchingExpenses[j]].getDate() > v)
                j--;

            if(i <= j)
            {
                buffer = indicesOfMatchingExpenses[i];
                indicesOfMatchingExpenses[i] = indicesOfMatchingExpenses[j];
                indicesOfMatchingExpenses[j] = buffer;
                i++;
                j--;
            }
    }
    while(i <= j);

    if(j > left)
            quicksortExpenses(left, j);
    if(i < right)
            quicksortExpenses(i, right);
}

