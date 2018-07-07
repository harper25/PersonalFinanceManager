#ifndef INCOME_H
#define INCOME_H

#include "CashItem.h"

class Income: public CashItem
{
    public:
        Income(int userId, std::string name, std::string date, float value);
        Income(int id, int userId, std::string name, std::string date, float value);
        int getNextId();

    protected:

    private:
        static int nextId;
};

#endif // INCOME_H
