/**
 * @file NMEAString.cpp
 * @brief Definition of the NMEAString class.
 * @author Mark Walsh
 * @verbatim
 *
 *     Program: Titan Program
 *     Version: 2.0.0
 *    Language: C++
 *     License: Licensed Material - Property of OceanGate, Inc
 *   Copyright: Copyright OceanGate, Inc (2018)
 *     Company: OceanGate, Inc.
 *     Address: 1205 Craftsman Way
 *              Suite 112
 *              Everett, WA
 *              98201
 *
 *      Author: Mark Walsh
 *       EMail: mwalsh@oceangate.com
 *
 *@endverbatim
 */

#include "NMEAString.h"
#include <sstream>

NMEA NMEA::create(std::string data)
{
    if (data.empty()) return NMEA();
    std::string::size_type pos = std::string::npos;
    if (data[0] == '$') {
        pos = data.find('*');
        if (pos != std::string::npos) {
            return NMEA(data);
        } else {
            return NMEA(data + "*" + getChecksum(data) + "\r\n");
        }
    } else return NMEA("$" + data + "*" + getChecksum(data) + "\r\n");
}

bool NMEA::isValid(NMEA data)
{
    if (data.length() < 2) return false;
    if (data[0] != '$') return false;
    std::string checksum, temp;
    std::string::size_type pos = data.find('*');
    if (pos == std::string::npos || pos > (data.length()-2)) return false;
    try {
        checksum = data.substr(pos+1, 2);
    } catch (std::out_of_range& e)
    {
        errMsg("Error (NMEA::isValid:36): " + std::string(e.what()));
        return false;
    }
    try {
        temp = getChecksum(data.substr(1, pos - 1));
    } catch (std::out_of_range& e)
    {
        errMsg("Error (NMEA::isValid:43): " + std::string(e.what()));
        return false;
    }
    //errMsg("Checksum: " + checksum + " Temp: " + temp);
    if (checksum == temp) return true;
    return false;
}

std::string NMEA::getChecksum(std::string data)
{
    if (data.empty()) return std::string();
    uint i = (data[0] == '$') ? 1 : 0;
    uchar cs = 0;
    for (; i < data.length(); i++) {
        if (data[i] == '\r' || data[i] == '\n' || data[i] == '*') break;
        cs ^= data[i];
    }
    return ucharToHex(cs);
}

std::vector<std::string> NMEA::getFields()
{
    std::string data(c_str());
    std::string::size_type startPos = find('$'), endPos = startPos;
    std::vector<std::string> vec;
    while (endPos != std::string::npos) {
        endPos = find_first_of(',' , startPos);
        if (endPos == std::string::npos) endPos = find('*', startPos);
        if (endPos != std::string::npos || startPos != std::string::npos) {
            try {
                if (endPos != startPos) vec.push_back(substr(startPos, endPos - startPos));
                else vec.push_back(std::string());
            } catch (std::out_of_range& e)
            {
                errMsg("Error (NMEA::getFields:77): " + std::string(e.what()));
                return vec;
            }
        }
        startPos = endPos + 1;
    }
    return vec;
}

bool NMEA::isValid()
{
    return isValid(*this);
}


