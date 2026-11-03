/**
 * @file UDPSSocket.h
 * @brief Definition of the UDPSSocket class.
 * @author Mark Walsh
 * @verbatim
 *
 *     Program: Cyclops Program
 *     Version: 1.0
 *    Language: C++
 *     License: Licensed Material - Property of OceanGate, Inc
 *   Copyright: Copyright OceanGate, Inc (2017)
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

#ifndef UDPSSOCKET_H_
#define UDPSSOCKET_H_

#include "SSocket.h"

/**
 *  UDP client and server.
 *
 *   Class: UDPSSocket
 * Purpose: UDP client and server
 *   Usage: UDPSSocket::createNewSocket()
 *
 *   This class opens two sockets, one to send and one to receive UDP data packets from a single ip/port.
 *   It could be stand-alone, but it is specifically designed for use inside a multi-socket communicator.
 *   Start off by calling createMe() to open and reserve the socket port.  Then add handshakes
 *   (pre-packaged data to elicit a response) by calling addHandshakes().  Send data via sendData() or
 *   sendHandshakes().  Receive data via receivePacket().
 *
 *   Sending and receiving messages via queue is also possible (and required for communicator).  Add messages via
 *   addOutgoingMessage() and receive messages via receiveMessages().  To send the outgoing messages call
 *   sendMessages().  To get received messages call getFirstMessage() until the message queue is empty.
 */
class UDPSSocket : public SSocket
{
public:
    /**
     * Default constructor.
     * No ports are opened.
     * @see createMe()
     */
    UDPSSocket();
    /**
     * Destructor.
     */
    virtual ~UDPSSocket();

    /**
     * Open and bind a socket connection.
     *
     * The incoming socket will be bound for listening and the outgoing socket will be opened for sending
     *
     * @param port port of destination
     * @param address address of destination
     * @param timeout_msecs timeout for receiving in milliseconds
     * @param device_name string to name socket (for display purposes only)
     * @return socket number (or error number)
     */
    virtual int createMe(int client_port, std::string address, int server_port, uint timeout_msecs, uint deviceType, int nBroadcast);
    void setServerAddress(std::string server_addr);

    /**
     * Receive UDP data and store it in buffer.
     * @return return value of recv
     */
    //virtual int receiveServerPacket();
    /**
     * Send data via the socket.
     * @param data the UDP packet to send
     * @return the return of sendto()
     */
    virtual int sendClientData(char *data, int nLen);
    virtual int sendServerData(char *data, int nLen);
    virtual int getServerData(char *pData);
    virtual int getClientData(char *pData);

protected:
    // for multicast
    struct ip_mreq* mreq;
};

#endif /* UDPLISTENER_H_ */
