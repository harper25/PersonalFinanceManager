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
        void showCurrentMonthBalanceSheet();
        void showPreviousMonthBalanceSheet();
        void showBalanceSheetForSelectedPeriod();
        void addIncome();
        void addExpense();
        void clearSettings();

    protected:

    private:
        std::vector <Income> incomes;
        std::vector <Expense> expenses;
        std::vector <int> indicesOfMatchingIncomes;
        std::vector <int> indicesOfMatchingExpenses;

        FileIncomes fileIncomes;
        FileExpenses fileExpenses;
        int loggedUserId;
        std::string loggedUserFullName;
        double incomesSum;
        double expensesSum;
        double balance;

        bool checkDate(std::string);
        CashItem defineNewCashItem();
        bool checkCashValue(std::string &valueString);
        double parseCashValue(std::string &valueString);
        std::string getCurrentDate();
        int getDaysCountForMonth(int month, int year);
        void showReturnMessage();
        void showSelectedCashItems();
        void quicksortIncomes(int left, int right);
        void quicksortExpenses(int left, int right);
};

#endif // CASHFLOWMANAGER_H
