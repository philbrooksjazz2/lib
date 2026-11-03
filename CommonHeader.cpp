/*
 * Logger.cpp
 *
 *  Created on: May 17, 2018
 *      Author: root
 */

#include <iostream>

#include "CommonHeader.h"

void errMsg(std::string str)
{
    std::cout << str << std::endl;

}

std::string ucharToHex(uchar num)
{
    std::string retVal;
    switch (num & 0xF0)
    {
        case 0x00: retVal = "0"; break;
        case 0x10: retVal = "1"; break;
        case 0x20: retVal = "2"; break;
        case 0x30: retVal = "3"; break;
        case 0x40: retVal = "4"; break;
        case 0x50: retVal = "5"; break;
        case 0x60: retVal = "6"; break;
        case 0x70: retVal = "7"; break;
        case 0x80: retVal = "8"; break;
        case 0x90: retVal = "9"; break;
        case 0xA0: retVal = "A"; break;
        case 0xB0: retVal = "B"; break;
        case 0xC0: retVal = "C"; break;
        case 0xD0: retVal = "D"; break;
        case 0xE0: retVal = "E"; break;
        case 0xF0: retVal = "F"; break;
    }
    switch (num & 0x0F)
    {
        case 0x0: retVal += "0"; break;
        case 0x1: retVal += "1"; break;
        case 0x2: retVal += "2"; break;
        case 0x3: retVal += "3"; break;
        case 0x4: retVal += "4"; break;
        case 0x5: retVal += "5"; break;
        case 0x6: retVal += "6"; break;
        case 0x7: retVal += "7"; break;
        case 0x8: retVal += "8"; break;
        case 0x9: retVal += "9"; break;
        case 0xA: retVal += "A"; break;
        case 0xB: retVal += "B"; break;
        case 0xC: retVal += "C"; break;
        case 0xD: retVal += "D"; break;
        case 0xE: retVal += "E"; break;
        case 0xF: retVal += "F"; break;
    }
    return retVal;
}

double decToDouble(std::string str)
{
    double retVal = 0.0;
    double base = .1;
    for (int i = str.length() - 1; i > -1; i--)
    {
        if (str[i] > 47 && str[i] < 58 && base < 1) retVal = retVal/10 + (str[i]-48)*base;
        else if (str[i] > 47 && str[i] < 58 && base >= 1) { retVal += base * (str[i]-48); base *= 10; }
        else if (str[i] == '.') base = 1;
        else if (i == 0 && str[i] == '-') retVal *= -1;
    }
    return retVal;
}

float decToFloat(std::string str)
{
    float retVal = 0.0;
    float base = .1;
    for (int i = str.length() - 1; i > -1; i--)
    {
        if (str[i] > 47 && str[i] < 58 && base < 1) retVal = retVal/10 + (str[i]-48)*base;
        else if (str[i] > 47 && str[i] < 58 && base >= 1) { retVal += base * (str[i]-48); base *= 10; }
        else if (str[i] == '.') base = 1;
        else if (i == 0 && str[i] == '-') retVal *= -1;
    }
    return retVal;
}

int decToInt(std::string str)
{
    int retVal = 0;
    int base = 1;
    for (int i = str.length() - 1; i > -1; i--)
    {
        if (str[i] > 47 && str[i] < 58) retVal += base * (str[i]-48);
        else if (i == 0 && str[i] == '-') retVal *= -1;
        else continue;
        base *= 10;
    }
    //ss << " Data out: " << retVal;
    //notify(ss.str());
    return retVal;
}


