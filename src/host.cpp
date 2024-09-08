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

        std::string host = "example.com";
        // std::string host = "2002::";  // Invalid IPv6 address, reserved for 6to4 mapping.

        auto m_socket_net = ENetSocketNetwork(host, 15000, NetworkAddressType::IPv6);
        std::cout << "info: socket Address: " << m_socket_net << '\n';

        switch (m_socket_net.ip_version()) {
                case (NetworkAddressType::IPv4): { std::cout << "IP Version: IPv4" << "\n"; break; }
                case (NetworkAddressType::IPv6): { std::cout << "IP Version: IPv6" << "\n"; break; }
                default: {}
        }

        m_ipv4_socket = new ENetSocket(&m_socket_net);

        try {
            m_ipv4_socket->connect();
            if (m_ipv4_socket->is_connected()) {
                std::cout << "Successfully created socket" << '\n';
            } else {
                std::cout << "Failed to create socket" << '\n';
            }
        }
        catch (enet_socket_error &err) {
            delete m_ipv4_socket;
            m_ipv4_socket = nullptr;
            std::cout << err.what() << "\n";
        }

    }

}

