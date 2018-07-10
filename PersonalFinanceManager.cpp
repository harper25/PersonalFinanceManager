#include <iostream>
#include <windows.h>
#include "User.h"
#include "Conversion.h"
#include "File.h"
#include "FileUsers.h"
#include "UsersManager.h"
#include "CashItem.h"
#include "Income.h"
#include "Expense.h"
#include "CashFlowManager.h"
#include "FileIncomes.h"
#include "FileExpenses.h"

using namespace std;

void showWelcomeMenu()
{
    system("cls");
    cout << "Personal Finance Manager" << endl << endl;
    cout << "1. Create a new account" << endl;
    cout << "2. Log in" << endl;
    cout << "9. Exit" << endl << endl;
}

void showUserMenu(string loggedUserFullName)
{
    system("cls");
    cout << "Personal Finance Manager --> User Menu " << endl;
    cout << "Logged as: " << loggedUserFullName << endl << endl;
    cout << "1. Add new income" << endl;
    cout << "2. Add new expense" << endl;
    cout << "3. Show balance sheet for current month" << endl;
    cout << "4. Show balance sheet for previous month" << endl;
    cout << "5. Show balance sheet for a given period of time" << endl;
    cout << "6. Show a complete balance sheet" << endl;
    cout << "7. Change password" << endl;
    cout << "8. Log out" << endl << endl;
}

int main()
{
    UsersManager usersManager;
    string choice;

    while(1)
    {
        showWelcomeMenu();
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
            usersManager.registerNewUser();
            break;
        case '2':
            usersManager.logging();
            if (usersManager.getLoggedUserId() != 0)
            {
                CashFlowManager cashFlowManager(usersManager.getLoggedUserId(), usersManager.getLoggedUserFullName());

                while (usersManager.getLoggedUserId() != 0)
                {
                    showUserMenu(usersManager.getLoggedUserFullName());
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
                        cashFlowManager.addIncome();
                        break;
                    case '2':
                        cashFlowManager.addExpense();
                        break;
                    case '3':
                        cashFlowManager.showCurrentMonthBalanceSheet();
                        break;
                    case '4':
                        cashFlowManager.showPreviousMonthBalanceSheet();
                        break;
                    case '5':
                        cashFlowManager.showBalanceSheetForSelectedPeriod();
                        break;
                    case '6':
                        cashFlowManager.showCompleteBalanceSheet();
                        break;
                    case '7':
                        usersManager.changePassword();
                        break;
                    case '8':
                        usersManager.setLoggedUserId(0);
                        usersManager.setLoggedUserFullName();
                        cashFlowManager.clearSettings();
                        break;
                    default:
                        cout << "Invalid choice!" << endl;
                        Sleep(1000);
                    }
                }
            }
            break;
        case '9':
            system("cls");
            cout << "Good bye!" << endl;
            exit(0);
        default:
            cout << "Invalid choice!" << endl;
            Sleep(1000);
        }
    }

    return 0;
}
