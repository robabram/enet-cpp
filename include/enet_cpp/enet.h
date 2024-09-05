//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
/**
 * @mainpage ENet CPP Library Documentation
 * @section intro_sec Introduction
 * A C++20 "Greenfield" implementation of the ENet reliable UDP networking library
 * @section install_sec Installation
 *
 * @subsection install_dependencies Installing Dependencies
 * Do somethings ...
 * @subsection install_library Installing Library
 * Do somethings ...
 * @subsection install_example Installing Examples
 * Do somethings ...
 */
#ifndef ENET_CPP_ENET_H
#define ENET_CPP_ENET_H

#include <string>

#include "enet_cpp/socket.h"

namespace enet {

    extern void hello();


    /******************************************************************************
     * Class ENetHost
     * This is the primary class for managing
     ******************************************************************************/
    class ENetHost {
    public:
        /**
         * EnetHost constructor
         * @param val The value
         * @param mul The mul
         */
        ENetHost(int val, int mul);

        ~ENetHost();

        void hello();

    private:
        int r;
        int mul;
        enet::ENetSocket *m_ipv4_socket;
        // enet::ENetSocket* m_ipv6_socket;
    };

}

#endif //ENET_CPP_ENET_H

