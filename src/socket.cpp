//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
#include <format>
#include <iostream>

#include "enet_cpp/error.h"
#include "enet_cpp/socket.h"


namespace enet {

    ENetSocket::ENetSocket(const ENetSocketNetwork& t_socket_net) :
            m_socket_net{t_socket_net},
            m_socket_handle{0},
            m_connected{false} { }

    ENetSocket::~ENetSocket() {
        disconnect();
    };

    void ENetSocket::connect() {

        m_socket_net.initialize();

        m_socket_handle = socket(m_socket_net.get_addrinfo_rec()->ai_family, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);
        if (m_socket_handle == ENET_INVALID_SOCKET) {
            std::string msg = std::format("Failed to create socket");
            throw socket_error(msg);
        }
        m_connected = true;
    };

    void ENetSocket::disconnect() {
        if (m_socket_handle) {
            std::cout << "Closing socket" << "\n";
            close(m_socket_handle);
            std::cout << "Socket closed" << "\n";
        }
        m_connected = false;
    }

    bool ENetSocket::is_connected() const { return m_connected; }

    auto ENetSocket::send_packet(const std::string& data, size_t size) -> int {
        return 0;
    }

}  // End namespace