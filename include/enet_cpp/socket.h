//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
#ifndef ENET_CPP_SOCKET_H
#define ENET_CPP_SOCKET_H


#include "enet_cpp/socket_net.h"

namespace enet {

    class ENetSocket {
    /**
     * A low level socket handler class for communicating with a system socket
     */
    public:
        /**
         * @brief Constructor
         * @param t_socket_net Pointer to an initialized ENetSocketNetwork object
         */
        explicit ENetSocket(ENetSocketNetwork *t_socket_net);
        /**
         * @brief Destructor
         */
        ~ENetSocket();
        /**
         * @brief Make a connection to the socket
         */
        void connect();

        /**
         * @brief Is the socket connected
         * @return True if socket is connected otherwise false
         */
        [[nodiscard]] bool is_connected() const;

        auto send_packet(const std::string &data, size_t size) -> int;

        // recv()

    private:
        ENetSocketNetwork *m_socket_net;  // ENetSocketNetwork object
        ENetCPPSocket m_socket_handle;  // System socket handle identifier
        bool m_connected;
    };

}  // End namespace

#endif //ENET_CPP_SOCKET_H
