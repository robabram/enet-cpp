//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
#include <iostream>
#include "enet_cpp/errors.h"
#include "enet_cpp/enet.h"
#include "enet_cpp/socket_net.h"
#include "enet_cpp/socket.h"

namespace enet {

    ENetHost::ENetHost(int val, int mul) :
            r{val},
            mul{mul},
            m_ipv4_socket{nullptr} {}

    ENetHost::~ENetHost() {

        if (m_ipv4_socket != nullptr) {
            std::cout << "Closing IPv4 socket" << "\n";
            delete this->m_ipv4_socket;
        }
    }

    void ENetHost::hello() {
        std::cout << "Hello = " << r * mul << "\n";

        auto m_socket_addr = ENetSocketNetwork("127.0.0.1", 10000);
        std::cout << "Socket Address : " << m_socket_addr << '\n';

        m_ipv4_socket = new ENetSocket(&m_socket_addr);

        try {
            m_ipv4_socket->connect();
            if (m_ipv4_socket->is_connected()) {
                std::cout << "Successfully created socket" << '\n';
            } else {
                std::cout << "Failed to create socket" << '\n';
            }
        }
        catch (enet_socket_error &err) {
            std::cout << err.what() << "\n";
        }

    }

}