//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
#ifndef ENET_CPP_ENET_H
#define ENET_CPP_ENET_H

#include <string>

#include "enet_cpp/socket.h"


extern void hello();


// -------------------------------------------------
class ENetHost {
public:
    ENetHost(int val, int mul);

    ~ENetHost();

    void hello();

private:
    int r;
    int mul;
    enet::ENetSocket* m_ipv4_socket;
};


#endif //ENET_CPP_ENET_H

