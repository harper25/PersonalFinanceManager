#include "Income.h"

int Income::nextId = 1;

Income::Income(int userId, std::string name, std::string date, double value)
{
    setId(nextId++);
    setUserId(userId);
    setName(name);
    setDate(date);
    setValue(value);
}

Income::Income(int id, int userId, std::string name, std::string date, double value)
{
    setId(id);
    setUserId(userId);
    setName(name);
    setDate(date);
    setValue(value);
    if (id >= nextId)
        nextId = id + 1;
}

int Income::getNextId()
{
    return nextId;
}


