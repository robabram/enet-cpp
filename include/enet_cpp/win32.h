//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//

#ifndef ENET_CPP_WIN32_H
#define ENET_CPP_WIN32_H

#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>

typedef SOCKET ENetCPPSocket;

#define ENET_INVALID_SOCKET INVALID_SOCKET

#define HTONS(value) (htons (value))
#define HTONL(value) (htonl (value))

#define NTONS(value) (ntohs (value))
#define NTONL(value) (ntohl (value))

#define ENET_API __declspec( dllimport )


#endif //ENET_CPP_WIN32_H
