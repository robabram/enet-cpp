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
#include <stdexcept>

#ifdef _WIN32
#include "enet_cpp/win32.h"
#else
#include "enet_cpp/unix.h"
#endif

#include "enet_cpp/enums.h"
#include "enet_cpp/errors.h"
#include "enet_cpp/socket.h"

namespace enet {

    /******************************************************************************
     * Class ENetHost
     * This is the primary class for managing a ENet CPP Host
     ******************************************************************************/
    class ENetHost {
    public:
        /**
         * @brief ENetHost Constructor
         * @param t_host IP address for socket to listen on, use '::' for dual stack socket
         * @param t_port The IP port to listen on. Value range is 1-65535
         * @param t_addr_type NetworkAddressType enum class value
         */
        ENetHost(const std::string &t_host, int t_port, NetworkAddressType t_addr_type);
        /**
         * @brief ENetHost Destructor
         */
        ~ENetHost();
        /**
         * @brief Create a network socket and start listening on it for traffic
         * @return 0 if socket setup was successful or -1 if there was an error
         */
        [[nodiscard]] int start();
        /**
         * @brief Stop listening for traffic and close network socket
         */
        void stop();
        /**
         * @brief Test if network socket is connected
         * @return True if network socket is connected and listening for traffic, otherwise False
         */
        [[nodiscard]] bool is_connected();

    private:
        enet::ENetSocket *m_socket;

    };

}

#endif //ENET_CPP_ENET_H

