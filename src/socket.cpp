//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
#include <cstring>
#include <format>
#include <utility>
#include <iostream>

#include "enet_cpp/socket.h"

namespace enet {

ENetSocket::ENetSocket(std::string t_addr, int t_port) :
        m_addr{std::move(t_addr)},
        m_port{t_port},
        m_str_port{std::format("{}", t_port)},
        m_addrinfo{nullptr},
        m_socket{0},
        m_connected{false}
{
}

ENetSocket::~ENetSocket() {
    std::cout << "Closing socket" << "\n";
    close(m_socket);
    freeaddrinfo(m_addrinfo);
    std::cout << "Socket closed" << "\n";
};

auto ENetSocket::connect() -> int {

    struct addrinfo hints{};
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;

    int result = getaddrinfo(m_addr.c_str(), m_str_port.c_str(), &hints, &m_addrinfo);

    if (result != 0 || m_addrinfo == nullptr)
    {
        // https://youtrack.jetbrains.com/issue/CPP-33258/stdformat-In-template-auto-in-return-type-deduced-as-typeidentitydouble-here-but-deduced-as-typeidentetyfloat-in-earlier-return
        std::string msg = std::format("Invalid address or port: {}:{}", m_addr, m_port);
        throw enet_socket_error(msg);
    }

    m_socket = socket(m_addrinfo->ai_family, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);
    if(m_socket == ENET_INVALID_SOCKET)
    {
        freeaddrinfo(m_addrinfo);
        std::string msg = std::format("Could not create socket for: {}:{}", m_addr, m_port);
        throw enet_socket_error(msg);
    }

    m_connected = true;

    return 0;
};

auto ENetSocket::is_connected() -> const bool {
    return m_connected;
}

auto ENetSocket::get_socket() const -> const int { return m_socket; };
auto ENetSocket::get_port() const -> const int {return m_port; };
auto ENetSocket::get_addr() const -> const std::string { return m_addr; }

auto ENetSocket::send_packet(const std::string &data, size_t size) -> int {
    return 0;
}




} // namespace