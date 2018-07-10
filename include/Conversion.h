#ifndef CONVERSION_H
#define CONVERSION_H

#include <string>
#include <sstream>
#include <iomanip>

class Conversion
{
    public:
        Conversion();
        int string2int(std::string);
        double string2double(std::string);
        template <typename T>
        std::string numberToString(T number)
        {
            std::ostringstream ss;
            ss.clear();
            ss << std::setprecision(16) << number;
            return ss.str();
        }

    protected:

    private:
};

#endif // CONVERSION_H
