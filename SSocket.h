/*
 * SSocket.h
 *
 *  Created on: April 14, 2020
 *      Author: Phil Brooks
 */

#ifndef SSOCKET_H_
#define SSOCKET_H_

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <deque>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#ifndef LOCAL_HEADER_H_
#include "CommonHeader.h"
#else
#include "../control/Header.h"
#endif

#define BUF_SIZE 8192

void c_errMsg(std::string str);

class SSocket 
{
public:
    SSocket(uint type);
    virtual ~SSocket();

    /**
     *
     * @param port
     * @param address
     * @param timeout_msecs
     * @param device_name
     * @return
     */
    virtual int createMe(int client_port, std::string address, int server_port, uint timeout_msecs, uint deviceType, int nBroadcast) = 0;

    /**
     * Receive data and store it in buffer.
     * @return return value of recv or read
     */
    //virtual int receiveServerPacket() = 0;

    /**
     * Get IP address of opened socket.
     * This is not the address the socket is tied to, rather the address of the destination.
     * @return string in the form of "XXX.XXX.XXX.XXX"
     */
    std::string getAddress();

    /**
     * Get display name of socket
     * @return string of the display name
     */
    uint getDeviceType();

    /**
     * Get port of opened socket.
     * This is not the port the socket is tied to, rather the port of the destination.
     * @return the port number
     */
    int getServerPort();
    int getClientPort();

    /**
     * The buffer for the recv or read function.
     * @return const pointer to the buffer
     */
    virtual int getServerData(char *pData) = 0;
    virtual int getClientData(char *pData) = 0;

    /**
     * Get the socket number.
     * @return the socket number from the call to socket()
     */
    int getSocket();

    /**
     * Send data via the socket.
     * @param data the UDP packet to send
     * @return the return of sendto()
     */
    virtual int sendServerData(char *pData, int nLen) = 0;
    virtual int sendClientData(char *pData, int nLen) = 0;

    /**
     * Clear the receive buffer.
     */
    void clearBuffer();

    /**
     * Returns whether or not data has been received recently
     * @return true if data has been received within the last 10 tries
     */
    bool status();

    /**
     * Change listener status to bad
     */
    void invalidateSSocket();

protected:
    uint m_device;
    std::string m_address;
    struct sockaddr_in m_si_server;
    struct sockaddr_in m_si_client;
    int m_nSocket;
    int m_nClientPort;
    int m_nServerPort;
    char m_buf[BUF_SIZE];
    struct timeval m_tv;
    uint m_type;
    int m_noCommsNum;
    uint m_nBytesRead;
};

#endif /* SSOCKET_H_ */
