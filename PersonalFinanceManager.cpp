#include <iostream>
#include "User.h"
#include "Conversion.h"
#include "File.h"
#include "FileUsers.h"
#include "UsersManager.h"
#include <windows.h>
#include "CashItem.h"
#include "Income.h"
#include "Expense.h"

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
    cout << "Personal Finance Manager --> User Menu: " << endl;
    cout << loggedUserFullName << endl << endl;
    cout << "1. " << endl;
    cout << "2. " << endl;
    cout << "3. " << endl;
    cout << "4. " << endl;
    cout << "5. " << endl;
    cout << "6. " << endl;
    cout << "7. Change password" << endl;
    cout << "8. Log out" << endl << endl;
}

int main()
{
    UsersManager usersManager;
    string choice;

    CashItem cashItem;
    cashItem.setId(3);
    cashItem.setName("cashItem");
    cashItem.setDate("2018-07-01");
    cout << "2018-07-01" << " " << cashItem.checkDate("2018-07-01") << endl;
    cashItem.setValue(123.45);

    cashItem.printCashItem();

    Income income(4, 56, "przychod", "2018-07-01", 65.42);
    cout << "2018-07-01" << " " << income.checkDate("2018-07-01") << endl;
    income.printCashItem();
    cout << "nextId: " << income.getNextId() << endl;
    cout << "userId: " << income.getUserId() << endl;

    Expense expense(2, 34, "wydatek", "2018-07-01", 123.45);
    cout << "2018-07-01" << " " << expense.checkDate("2018-07-01") << endl;
    expense.printCashItem();
    cout << "nextId: " << expense.getNextId() << endl;
    cout << "userId: " << expense.getUserId() << endl;


    while(0)
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
//                ContactsManager contactsManager(usersManager.getLoggedUserId());

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
                        break;
                    case '2':
                        break;
                    case '3':
                        break;
                    case '4':
                        break;
                    case '5':
                        break;
                    case '6':
                        break;
                    case '7':
                        usersManager.changePassword();
                        break;
                    case '8':
                        usersManager.setLoggedUserId(0);
                        usersManager.setLoggedUserFullName();
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
