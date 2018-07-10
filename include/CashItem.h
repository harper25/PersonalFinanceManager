#ifndef CASHITEM_H
#define CASHITEM_H

#include <string>

class CashItem
{
    public:
        CashItem();
        CashItem(std::string name, std::string date, double value);
        int getId();
        void setId(int id);
        int getUserId();
        void setUserId(int userId);
        std::string getName();
        void setName(std::string name);
        std::string getDate();
        void setDate(std::string date);
        double getValue();
        void setValue(double value);
        void printCashItem();

    protected:
        int id;
        int userId;
        std::string name;
        std::string date;
        double value;

    private:
};

#endif // CASHITEM_H
