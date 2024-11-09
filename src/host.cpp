//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
#include <iostream>
#include "enet_cpp/enet.h"

namespace enet {


    ENetHost::ENetHost(const std::string &t_host, int t_port, NetworkAddressType t_addr_type) {
        m_socket = new ENetSocket(ENetSocketNetwork(t_host, t_port, t_addr_type));
    }

    ENetHost::~ENetHost() {

        if (m_socket != nullptr) {
            std::cout << "Closing host socket" << "\n";
            delete this->m_socket;
        }
    }

    int ENetHost::start() {

        std::cout << "Starting host server" << '\n';

        try {
            m_socket->connect();
            if (m_socket->is_connected()) {
                std::cout << "Successfully created socket" << '\n';
                return 0;
            }
            std::cout << "Failed to create socket" << '\n';
        }
        catch (socket_error &err) {
            std::cout << err.what() << "\n";
        }

        return -1;
    }

    void ENetHost::stop() {
        m_socket->disconnect();
        std::cout << "Host server has stopped" << '\n';
    }

    bool ENetHost::is_connected() {
        return m_socket->is_connected();
    }

}

