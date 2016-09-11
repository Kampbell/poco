//
// The contents of this file are subject to the Mozilla Public
// License Version 1.1 (the "License"); you may not use this file
// except in compliance with the License. You may obtain a copy
// of the License at http://www.mozilla.org/MPL/
// 
// Software distributed under the License is distributed on an
// "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
// implied. See the License for the specific language governing
// rights and limitations under the License.
// 
// The Original Code is State Machine Compiler (SMC).
// 
// The Initial Developer of the Original Code is Charles W. Rapp.
// Portions created by Charles W. Rapp are
// Copyright (C) 2000 - 2003 Charles W. Rapp.
// All Rights Reserved.
// 
// Contributor(s): 
//
// Name
//  TcpClient.cpp
//
// Description
//  TCP client connection class implementation.
//
// RCS ID
// $Id: TcpClient.cpp,v 1.5 2007/12/28 12:34:40 cwrapp Exp $
//
// CHANGE LOG
// $Log: TcpClient.cpp,v $
// Revision 1.5  2007/12/28 12:34:40  cwrapp
// Version 5.0.1 check-in.
//
// Revision 1.4  2005/05/28 13:31:18  cwrapp
// Updated C++ examples.
//
// Revision 1.0  2003/12/14 19:39:43  charlesr
// Initial revision
//

#include "TcpClient.h"
#if defined (WIN32)
#include <winsock2.h>
#else
#  if defined(__sun)
#include <sys/systeminfo.h>
#  else
#include <unistd.h>
#  endif
#include <netdb.h>
#endif

// Const declarations.
const static long MAX_HOSTNAME_LEN = 257;

//---------------------------------------------------------------
// TcpClient(TcpConnectionListener&) (Public)
// Create an unconnected TCP client.
//
TcpClient::TcpClient(TcpConnectionListener& listener)
: TcpConnection(listener)
{}

//---------------------------------------------------------------
// ~TcpClient() (Public)
// Destructor.
//
TcpClient::~TcpClient()
{}

//---------------------------------------------------------------
// getServerAddress() const (Public)
// This client is connected to this TCP service.
//
const SocketAddress& TcpClient::getServerAddress() const
{
    return(_farAddress);
} // end of TcpClient::getServerAddress() const

//---------------------------------------------------------------
// getClientPort() const (Public)
// This client's TCP port.
//
unsigned short TcpClient::getClientPort() const
{
    return(_nearAddress.port());
} // end of TcpClient::getClientPort() const

//---------------------------------------------------------------
// open(unsigned short) (Public)
// Open a client connection to a local TCP service.
//
void TcpClient::open(unsigned short port)
{
    SocketAddress address;
    char hostname[MAX_HOSTNAME_LEN];
    hostent *hostentry;

    // Get the local address.
#if defined(__sun)
    sysinfo(SI_HOSTNAME, hostname, MAX_HOSTNAME_LEN);
#else
    gethostname(hostname, MAX_HOSTNAME_LEN);
#endif
    hostentry = gethostbyname(hostname);

    // Fill in the destination address.
//    address.port() = port;
//    memcpy(&(address.sin_addr.s_addr),  hostentry->h_addr_list[0], 4);

    activeOpen(address);

    return;
} // end of TcpClient::open(unsigned short)

//---------------------------------------------------------------
// open(const SocketAddress&) (Public)
// Open a client connection to a remove TCP service.
//
void TcpClient::open(const SocketAddress& address)
{
    activeOpen(address);
    return;
} // end of TcpClient::open(const SocketAddress&)

//---------------------------------------------------------------
// TcpClient(const SocketAddress&, ...) (Private)
// Create an "accepted" client connection.
//
TcpClient::TcpClient(const SocketAddress& far_address,
                     const SocketAddress& near_address,
                     unsigned short actual_port,
                     DatagramSocket udp_socket,
                     unsigned long sequence_number,
                     TcpServer& server,
                     TcpConnectionListener& listener)
: TcpConnection(far_address,
                near_address,
                actual_port,
                udp_socket,
                sequence_number,
                server,
                listener)
{}
