/*
 * CommonHeader.h
 *
 *  Created on: May 17, 2018
 *      Author: root
 */
#ifndef LOCALHEADER_H_

#ifndef COMMONHEADER_H_
#define COMMONHEADER_H_

#include <string>
#include <sstream>
#include <cstdint>
#include <sys/types.h>
#include <queue>
#include <cmath>

#define uint unsigned int
#define uchar unsigned char
#define ulong unsigned long

#define DEPTH_IPC_LPORT  53007
#define DEPTH_BCAST_PORT 5103
#define AE_DATA_DIR "/AEData"
#define TEST_KEY_LEN 12

enum __ConnectionTypes {
    TYPE_TCP,
    TYPE_UDP
};

#define MAX_TIMEOUT 200

template <class T> std::string stringify(T data) {
    static std::stringstream ss;
    ss << data;
    std::string retVal(ss.str());
    ss.str(std::string());
    return retVal;
}

typedef struct _AESample
{
    int    meta1;
    int    meta2;
    short  aeData[8];
    short  chks0;
    short  chks1;
    int    timestamp;
} AESample;


void errMsg(std::string str);

int decToInt(std::string str);
double decToDouble(std::string str);
float decToFloat(std::string str);

std::string ucharToHex(uchar num);

typedef struct __socket
{
    int inPort;
    int outPort;
    std::string address;
    __socket() : inPort(0), outPort(0), address("") {}
    __socket(int _inPort, std::string _address, int _outPort) : inPort(_inPort), outPort(_outPort), address(_address) {}
    __socket(const __socket& socket) : inPort(socket.inPort), outPort(socket.outPort), address(socket.address) {}
} _socket;

#endif /* COMMONHEADER_H_ */
#endif /* LOCALHEADER_H_ */
