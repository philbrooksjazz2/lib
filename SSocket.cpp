/*
 * SSocket.cpp
 *
 *  Created on: Nov 6, 2017
 *      Author: Phil Brooks
 */

#include "SSocket.h"
#include <cstring>
#include <stdlib.h>
#include <sstream>

void c_errMsg(std::string str)
{
    std::cout << str << std::endl;

}



SSocket::SSocket(uint aType) : m_device(0), m_nSocket(-1), m_type(aType), m_noCommsNum(0) {}

SSocket::~SSocket() {}

bool SSocket::status()
{
    return (m_noCommsNum < 10) ? true : false;
}

std::string SSocket::getAddress()
{
    return inet_ntoa(m_si_client.sin_addr);
}

uint SSocket::getDeviceType()
{
    return m_device;
}

int SSocket::getClientPort()
{
    return ntohs(m_si_client.sin_port);
}

//uint SSocket::getServerData(char *pData, int nSize)
//{
//    memcpy(pData,m_buf,nSize);
//    return nSize;
//}

int SSocket::getSocket()
{
    return m_nSocket;
}

void SSocket::clearBuffer()
{
    memset(m_buf,0,strlen(m_buf));
}

void SSocket::invalidateSSocket()
{
    m_noCommsNum = 11;
}


