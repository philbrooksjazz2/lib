/*
 * UDPSSocket.cpp
 *
 *  Created on: April 14, 2020
 *      Author: Phil Brooks
 */
#include "UDPSSocket.h"
#include <libexplain/socket.h>
#include <libexplain/bind.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdexcept>


UDPSSocket::UDPSSocket() : SSocket(TYPE_UDP), mreq(NULL) 
{
    // TODO Auto-generated constructor stub

}

UDPSSocket::~UDPSSocket() 
{
    if (mreq) delete mreq;
}

int UDPSSocket::createMe(int client_port, std::string destination_address, int server_port, uint timeout_msecs, uint deviceType, int nBroadcast)
{
    int nRet = 0;
    if ((m_nSocket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP)) == -1) 
    {
        c_errMsg(explain_socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP));
        return -1;
    }
    c_errMsg("UDP Socket Creation - Good");

    m_tv.tv_sec = timeout_msecs/1000;
    m_tv.tv_usec = timeout_msecs%1000;
    int reuse = 1;

    c_errMsg("client port = "  + stringify<int>(client_port));
    c_errMsg("server port = "  + stringify<int>(server_port));

    if ( nBroadcast == 1 )
    {
        nRet = setsockopt(m_nSocket, SOL_SOCKET, SO_BROADCAST, &nBroadcast, sizeof(nBroadcast));
        if ( nRet == -1 )
        {
            printf("Error setting broadcast enable\n");
        }
    }
    setsockopt(m_nSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&m_tv, sizeof(struct timeval));
    setsockopt(m_nSocket, SOL_SOCKET, SO_REUSEPORT, (const char*)&(reuse), sizeof(reuse));
    setsockopt(m_nSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&(reuse), sizeof(reuse));

    m_si_server.sin_family = AF_INET;
    m_si_server.sin_port = htons(server_port);       

    (m_si_server.sin_addr).s_addr= htonl(INADDR_ANY);

    if ( nBroadcast == 1 )
    {
        (m_si_server.sin_addr).s_addr= htonl(INADDR_BROADCAST);
    }
    //(m_si_server.sin_addr).s_addr = inet_addr(destination_address.c_str());

    if(bind(m_nSocket, (struct sockaddr*)&m_si_server, sizeof(struct sockaddr_in)) == -1) 
    {
        //c_errMsg(explain_bind(m_nSocket, (struct sockaddr*) &m_si_server, sizeof(struct sockaddr_in)));
        //c_errMsg("UDP Socket Creation - Bad Bind");
        return -1;
    }

    char addr[16] = "";
    ioctl(m_nSocket, SIOCGIFADDR, addr);
    m_address = addr;

    m_si_client.sin_family = AF_INET;
    m_si_client.sin_addr.s_addr = inet_addr(destination_address.c_str());
    m_si_client.sin_port = htons(client_port);

    c_errMsg("UDP Bind - Good");
    m_device = deviceType;
    return m_nSocket;
}
void UDPSSocket::setServerAddress(std::string server_addr)
{
    (m_si_server.sin_addr).s_addr = inet_addr(server_addr.c_str());
}
int UDPSSocket::getServerData(char *pData)
{
    unsigned int slen = sizeof(struct sockaddr_in);
    int retVal = recvfrom(m_nSocket, m_buf, BUF_SIZE, 0, (struct sockaddr*) &m_si_server, &slen);
    m_nBytesRead = retVal;
    if (retVal < 1) 
    { 
        //m_noCommsNum++; 
        //printf("UDPSSocket - getServerData read -1\n");
        return retVal; 
    }
    c_errMsg("UDPSSocket - getServerData read bytecount "  + stringify<int>(retVal));
    //m_noCommsNum = 0;
    memcpy(pData,m_buf,m_nBytesRead);
    return m_nBytesRead;
}
int UDPSSocket::getClientData(char *pData)
{
    unsigned int slen = sizeof(struct sockaddr_in);
    int retVal = recvfrom(m_nSocket, m_buf, BUF_SIZE, 0, (struct sockaddr*) &m_si_client, &slen);
    m_nBytesRead = retVal;
    if (retVal < 1) 
    { 
        //m_noCommsNum++; 
        //printf("UDPSSocket - getClientData read -1\n");
        return retVal; 
    }
    c_errMsg("UDPSSocket - getClientData read bytecount "  + stringify<int>(retVal));
    //m_noCommsNum = 0;
    memcpy(pData,m_buf,m_nBytesRead);
    return m_nBytesRead;
}
#ifdef NOT
uint UDPSSocket::receiveServerPacket(char *pData)
{
    unsigned int slen = sizeof(struct sockaddr_in);
    c_errMsg("Device: " + stringify<int>(device));
    int retVal = recvfrom(m_nSocket, m_buf, 8192, 0, (struct sockaddr*) &m_si_server, &slen);
    m_nBytesRead = retVal;
    if (retVal < 1) 
    { 
        m_noCommsNum++; 
        printf("UDPSSocket - receiveServerPacket read -1\n");
        return retVal; 
    }
    //errMsg("UDPSSocket - receiveServerPacket read bytecount "  + stringify<int>(retVal));
    m_noCommsNum = 0;
    return retVal;
}
#endif //NOT
int UDPSSocket::sendServerData(char *pBuf, int nLen)
{
    unsigned int slen = sizeof(struct sockaddr_in);
    int retVal = sendto(m_nSocket, pBuf, nLen, 0, (struct sockaddr*) &m_si_server, slen);
    //int retVal = send(m_nSocket, pBuf, nLen, 0 );
    if (retVal < 0) 
    { 
        m_noCommsNum++; 
        return retVal; 
    }
    return retVal;
}

int UDPSSocket::sendClientData(char *pBuf, int nLen)
{
    unsigned int slen = sizeof(struct sockaddr_in);
    int retVal = sendto(m_nSocket, pBuf, nLen, 0, (struct sockaddr*) &m_si_client, slen);
    //int retVal = send(m_nSocket, pBuf, nLen, 0 );
    if (retVal < 0) 
    { 
        m_noCommsNum++; 
        return retVal; 
    }
    return retVal;
}

