#ifndef EXPENSE_H
#define EXPENSE_H

#include "CashItem.h"

class Expense : public CashItem
{
    public:
        Expense(int userId, std::string name, std::string date, float value);
        Expense(int id, int userId, std::string name, std::string date, float value);
        int getNextId();

    protected:

    private:
        static int nextId;
};

#endif // EXPENSE_H
