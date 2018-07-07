#ifndef CASHITEM_H
#define CASHITEM_H

#include <string>

class CashItem
{
    public:
        CashItem();
        int getId();
        void setId(int id);
        int getUserId();
        void setUserId(int userId);
        std::string getName();
        void setName(std::string name);
        std::string getDate();
        void setDate(std::string date);
        float getValue();
        void setValue(float value);
        void printCashItem();

        bool checkDate(std::string);

    protected:
        int id;
        int userId;
        std::string name;
        std::string date;
        float value;

        float parseCashValue(std::string);
        std::string getCurrentDate();
        int getMonthDaysCount(int month, int year);

    private:
};

#endif // CASHITEM_H
