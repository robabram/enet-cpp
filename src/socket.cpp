//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
#include <cstring>
#include <format>
#include <iostream>

#include "enet_cpp/errors.h"
#include "enet_cpp/address.h"
#include "enet_cpp/socket.h"


namespace enet {

//!
//! \param t_addr
//! \param t_port
    ENetSocket::ENetSocket(ENetSocketAddress &t_addr) :
            m_socket_addr{t_addr},
            m_socket_addrinfo{nullptr},
            m_socket_handle{0},
            m_connected{false} {
    }

    ENetSocket::~ENetSocket() {
        std::cout << "Closing socket" << "\n";
        close(m_socket_handle);
        freeaddrinfo(m_socket_addrinfo);
        std::cout << "Socket closed" << "\n";
    };

    auto ENetSocket::connect() -> int {

        struct addrinfo hints{};
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_protocol = IPPROTO_UDP;

        auto [m_addr, m_port] = m_socket_addr.get_socket_net();
        std::string s_port = std::format("{}", m_port);

        int result = getaddrinfo(m_addr.c_str(), s_port.c_str(), &hints, &m_socket_addrinfo);

        if (result != 0 || m_socket_addrinfo == nullptr) {
            // https://youtrack.jetbrains.com/issue/CPP-33258/stdformat-In-template-auto-in-return-type-deduced-as-typeidentitydouble-here-but-deduced-as-typeidentetyfloat-in-earlier-return
            std::string msg = std::format("Invalid address or port: {}:{}", m_addr, m_port);
            throw enet_socket_error(msg);
        }

        m_socket_handle = socket(m_socket_addrinfo->ai_family, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);
        if (m_socket_handle == ENET_INVALID_SOCKET) {
            freeaddrinfo(m_socket_addrinfo);
            std::string msg = std::format("Could not create socket for: {}:{}", m_addr, m_port);
            throw enet_socket_error(msg);
        }

        m_connected = true;

        return 0;
    };

    auto ENetSocket::is_connected() -> const bool {
        return m_connected;
    }

    int ENetSocket::get_socket_handle() const { return m_socket_handle; };

    auto ENetSocket::send_packet(const std::string &data, size_t size) -> int {
        return 0;
    }

    const ENetSocketAddress& ENetSocket::get_addr() const {
        return m_socket_addr;
    }

} // namespace