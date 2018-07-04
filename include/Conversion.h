#ifndef CONVERSION_H
#define CONVERSION_H

#include <string>
#include <sstream>

class Conversion
{
    public:
        Conversion();
        int string2int(std::string);
        float string2float(std::string);
        template <typename T>
        std::string numberToString(T number)
        {
            std::ostringstream ss;
            ss.clear();
            ss << number;
            return ss.str();
        }

    protected:

    private:
};

#endif // CONVERSION_H
