//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//

#ifndef ENET_CPP_UNIX_H
#define ENET_CPP_UNIX_H

#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

typedef int ENetCPPSocket;

#define ENET_INVALID_SOCKET -1

#define HTONS(value) (htons (value))
#define HTONL(value) (htonl (value))

#define NTONS(value) (ntohs (value))
#define NTONL(value) (ntohl (value))

#define ENET_API extern

#endif //ENET_CPP_UNIX_H
