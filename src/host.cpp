//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
#include <iostream>
#include "enet_cpp/enet.h"
#include "enet_cpp/socket.h"

using namespace enet;

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
    m_ipv4_socket = new ENetSocket("127.0.0.1", 10000);
    try {
        auto result = m_ipv4_socket->connect();
        std::cout << "Successfully connected socket" << '\n';
    }
    catch (enet_socket_error &err) {
        std::cout << err.what() << "\n";
    }

}