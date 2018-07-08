#ifndef FILEEXPENSES_H
#define FILEEXPENSES_H

#include "File.h"
#include "Expense.h"
#include <string>
#include <vector>

class FileExpenses : public File
{
    public:
        FileExpenses(std::string);

        void loadDataFromXML();
        void addNewItemToXML(Expense &newExpense);
        void updateXML(std::vector <Expense> &expenses);

        std::vector <Expense> readExpensesFromXML(int loggedUserId);

    protected:

    private:
};

#endif // FILEEXPENSES_H
