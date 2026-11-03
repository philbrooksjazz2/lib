/**
 * @file NMEAString.h
 * @brief Declaration of the NMEAString class.
 * @author Mark Walsh
 * @verbatim
 *
 *     Program: Titan Program
 *	   Version: 2.0.0
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

#ifndef NMEASTRING_H_
#define NMEASTRING_H_

#include <vector>

#include "CommonHeader.h"

class NMEA : public std::string
{
public:
	NMEA() {}
	NMEA(std::string data) : std::string(data) {}
	virtual ~NMEA() {}
	// Static Members
	/**
	 * Create a NMEA String from a string of data.
	 * @warning Does not check validity of NMEA string!
	 * @see isValid(NMEA data)
	 * @param data The data string to convert
	 * @return An NMEA string containing the desired data (with checksum)
	 */
	static NMEA create(std::string data);
	/**
	 *
	 * @param data
	 * @return
	 */
	static bool isValid(NMEA data);
	/**
	 * This will calculate the checksum needed for the string
	 * @param The string to be checked
	 * @return The 2 digit checksum (ASCII hex)
	 */
	static std::string getChecksum(std::string);

	// Non-Static Members
	/**
	 *
	 * @param data
	 * @return
	 */
	std::vector<std::string> getFields();
	/**
	 *
	 * @return
	 */
	bool isValid();
};

#endif /* NMEASTRING_H_ */
