#include "Expense.h"

int Expense::nextId = 1;

Expense::Expense(int userId, std::string name, std::string date, double value)
{
    setId(nextId++);
    setUserId(userId);
    setName(name);
    setDate(date);
    setValue(value);
}

Expense::Expense(int id, int userId, std::string name, std::string date, double value)
{
    setId(id);
    setUserId(userId);
    setName(name);
    setDate(date);
    setValue(value);
    if (id >= nextId)
        nextId = id + 1;
}

int Expense::getNextId()
{
    return nextId;
}


