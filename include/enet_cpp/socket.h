//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
#ifndef ENET_CPP_SOCKET_H
#define ENET_CPP_SOCKET_H

#ifdef _WIN32
#include "enet_cpp/win32.h"
#else
#include "enet_cpp/unix.h"
#endif

#include "enet_cpp/address.h"

namespace enet {

    class ENetSocket {
    public:
        /**
         * Class constructor
         * @param t_addr
         * @param t_port
         */
        ENetSocket(ENetSocketAddress& t_addr);
        ~ENetSocket();

        auto connect() -> int;

        int get_socket_handle() const;  /**< Return the system socket handle identifier */
        const ENetSocketAddress& get_addr() const;  /**< Return the bound IP address */
        auto is_connected() -> const bool;  /**< True if socket is connected otherwise false */

        auto send_packet(const std::string &data, size_t size) -> int;

        // recv()

    private:
        ENetSocketAddress m_socket_addr;  /**< Socket address object */

        ENetCPPSocket m_socket_handle;  /**< System socket handle identifier */
        struct addrinfo *m_socket_addrinfo;  /**< System address info record pointer */
        bool m_connected;
    };

} // namespace enet_socket

#endif //ENET_CPP_SOCKET_H
