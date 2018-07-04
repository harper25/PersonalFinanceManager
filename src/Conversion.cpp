#include "Conversion.h"

using namespace std;

Conversion::Conversion()
{
}

int Conversion::string2int(string number)
{
    return atoi(number.c_str());
}

float Conversion::string2float(string number)
{
    return atof(number.c_str());
}


