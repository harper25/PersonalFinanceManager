#ifndef FILEINCOMES_H
#define FILEINCOMES_H

#include "File.h"
#include "Income.h"
#include <string>
#include <vector>

class FileIncomes : public File
{
    public:
        FileIncomes(std::string);

        void loadDataFromXML();
        void addNewItemToXML(Income &newIncome);
        void updateXML(std::vector <Income> &incomes);

        std::vector <Income> readIncomesFromXML(int loggedUserId);
    protected:

    private:
};

#endif // FILEINCOMES_H
