#ifndef CASHFLOWMANAGER_H
#define CASHFLOWMANAGER_H

#include "CashItem.h"
#include "Income.h"
#include "Expense.h"
#include "FileIncomes.h"
#include "FileExpenses.h"
#include <string>
#include <vector>


class CashFlowManager
{
    public:
        CashFlowManager(int loggedUserId, std::string loggedUserFullName,
                        std::string = "fileIncomes.xml", std::string = "fileExpenses.xml");
        std::string getLoggedUserFullName();
        void setLoggedUserFullName(std::string = "");
        int getLoggedUserId();
        void setLoggedUserId(int);
        void showCompleteBalanceSheet();
        void addIncome();
        void addExpense();

    protected:

    private:
        std::vector <Income> incomes;
        std::vector <Expense> expenses;
        FileIncomes fileIncomes;
        FileExpenses fileExpenses;
        int loggedUserId;
        std::string loggedUserFullName;
        float incomesSum;
        float expensesSum;
        float balance;

        bool checkDate(std::string);
        CashItem defineNewCashItem();
        bool checkCashValue(std::string &valueString);
        float parseCashValue(std::string &valueString);
        std::string getCurrentDate();
        int getDaysCountForMonth(int month, int year);
        void showReturnMessage();
};

#endif // CASHFLOWMANAGER_H
