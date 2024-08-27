//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
#ifndef ENET_CPP_SOCKET_H
#define ENET_CPP_SOCKET_H

#include <stdexcept>

#ifdef _WIN32
#include "enet_cpp/win32.h"
#else
#include "enet_cpp/unix.h"
#endif

namespace enet {

    class enet_socket_error : public std::runtime_error {
    public:
        explicit enet_socket_error(const std::string &t_err_msg) : std::runtime_error(t_err_msg) {}
    };


    class ENetSocket {
    public:
        ENetSocket(std::string t_addr, int t_port);
        ~ENetSocket();

        auto connect() -> int;

        auto get_socket() const -> const int;
        auto get_port() const -> const int;
        auto get_addr() const -> const std::string;
        auto is_connected() -> const bool;

        auto send_packet(const std::string &data, size_t size) -> int;

        // recv()

    private:
        ENetCPPSocket m_socket;
        int m_port;
        std::string m_str_port;
        std::string m_addr;
        struct addrinfo *m_addrinfo;
        bool m_connected;
    };

} // namespace enet_socket

#endif //ENET_CPP_SOCKET_H
