//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
#ifndef ENET_CPP_SOCKET_NET_H
#define ENET_CPP_SOCKET_NET_H

#include <string>

#ifdef _WIN32
#include "enet_cpp/win32.h"
#else
#include "enet_cpp/unix.h"
#endif


namespace enet {

    /**
     * A class to encapsulate the network address and port that a socket will use.  Includes validating
     * the address and port, creating the address info record used when creating a socket. Throws an
     * "enet_socket_error" exception when there is an invalid IP, port or the address info record creation
     * fails
     */
    class ENetSocketNetwork {

    public:
        /**
         * Create a new socket network information object containing an IP address and Port number
         * @brief Constructor
         * @param t_addr Valid IPv4 or IPv6 address string
         * @param t_port  Valid integer value between 0 and 65535. 0-1023 are reserved ports
         */
        ENetSocketNetwork(std::string t_addr, int t_port);
        /**
         * @brief Destructor
         */
        ~ENetSocketNetwork();
        /**
         * @brief Return the pointer to the system allocated "addrinfo" record
         * @return Pointer to addrinfo
         */
        [[nodiscard]] addrinfo *get_addrinfo_rec() const;
        /**
         * @brief Return the IP Address and Port value as a pair
         * @return IP Address, Port
         */
        [[nodiscard]] std::pair<const std::string, int> get_socket_net() const;
        /**
         * @brief Determine if the stored IP address and Port is valid
         * @return True if IP address and port are valid else False
         */
        [[nodiscard]] bool is_valid() const;
        /**
         * @brief Determine if the stored IP address is an IPv4 address
         * @return True if IPv4 address else False
         */
        [[nodiscard]] bool is_ipv4() const;
        /**
         * @brief Determine if the stored IP address is an IPv6 address
         * @return True if IPv6 address else False
         */
        [[nodiscard]] bool is_ipv6() const;
        /**
         * @brief Stream overloading
         * @param os Stream handle object
         * @param t Reference to ENetSocketNetwork object
         * @return Return IP address and Port values as a string, delimited by a colon.
         */
        friend std::ostream &operator<<(std::ostream &os, const ENetSocketNetwork &t);

    private:
        void make_addr_info();

        std::string m_addr;
        int m_port;

        bool m_valid;
        bool m_ipv4;
        bool m_ipv6;

        struct addrinfo *m_socket_addrinfo;  // System address info record pointer
    };

}  // End namespace

#endif //ENET_CPP_SOCKET_NET_H
