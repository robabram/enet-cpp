//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
#include <iostream>
#include "enet_cpp/errors.h"
#include "enet_cpp/enet.h"
#include "enet_cpp/address.h"
#include "enet_cpp/socket.h"

namespace enet {

    ENetHost::ENetHost(int val, int mul) :
            r{val},
            mul{mul},
            m_ipv4_socket{nullptr} {}

    ENetHost::~ENetHost() {
        this->r = 1;
        if (m_ipv4_socket != nullptr) {
            std::cout << "Closing IPv4 socket" << "\n";
            delete this->m_ipv4_socket;
            m_ipv4_socket = nullptr;
        }
    }

    void ENetHost::hello() {
        std::cout << "Hello = " << r * mul << "\n";

        auto m_socket_addr = ENetSocketAddress("127.0.0.1", 10000);
        std::cout << "Socket Address : " << m_socket_addr << '\n';

        m_ipv4_socket = new ENetSocket(m_socket_addr);

        try {
            auto result = m_ipv4_socket->connect();
            std::cout << "Successfully connected socket" << '\n';
        }
        catch (enet_socket_error &err) {
            std::cout << err.what() << "\n";
        }

    }

}