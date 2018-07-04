#include <iostream>
#include "User.h"
#include "Conversion.h"
#include "File.h"
#include "FileUsers.h"
#include "UsersManager.h"
#include <windows.h>

using namespace std;

void showWelcomeMenu()
{
    system("cls");
    cout << "Personal Finance Manager" << endl << endl;
    cout << "1. Create a new account" << endl;
    cout << "2. Log in" << endl;
    cout << "9. Exit" << endl << endl;
}

void showUserMenu()
{
    system("cls");
    cout << "Personal Finance Manager --> User Menu: " << endl << endl;
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
//                ContactsManager contactsManager(usersManager.getLoggedUserId());

                while (usersManager.getLoggedUserId() != 0)
                {
                    showUserMenu();
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
