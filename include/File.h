#ifndef FILE_H
#define FILE_H
#include <string>
#include "Markup.h"
#include "Conversion.h"

class File
{
public:
    File();
    virtual void loadDataFromXML() = 0;
    std::string getFilename();

protected:
    std::string filename;
    CMarkup xml;
    Conversion conversion;

private:
};

#endif // FILE_H
