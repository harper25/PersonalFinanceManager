#include "Conversion.h"

using namespace std;

Conversion::Conversion()
{
}

int Conversion::string2int(string number)
{
    return atoi(number.c_str());
}

double Conversion::string2double(string number)
{
    return atof(number.c_str());
}


