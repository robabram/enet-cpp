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
     * Indicates the either a choice of IP version to use or what IP version is in use.
     */
    enum class NetworkAddressType {
        Any, IPv4, IPv6
    };

    /**
     * A class to encapsulate the network address and port that a socket will use.  Includes validating
     * the address and port, creating the address info record used when creating a socket. Throws an
     * "enet_socket_error" exception when there is an invalid IP, port or the address info record creation
     * fails.
     */
    class ENetSocketNetwork {

    public:
        /**
         * Create a new socket network information object containing an IP address and Port number. To setup
         * a dual stack network, set 't_host' to '::' and 't_type' to 'Any".  If 't_host' is a domain name
         * (IE: 'example.com' and 't_type' is 'Any', then the IP version is chosen by the the DNS entries returned.
         * Setting 't_type' to 'IPv4' or 'IPv6' will cause the DNS lookup to only return addresses that match the type.
         * If 't_host' is an IP address, 't_type' is ignored and will be forced to the correct IP address family type.
         * @brief Constructor
         * @param t_host Valid IPv4/IPv6 address string, or domain host name. If t_host is IP addr, type arg is ignored
         * @param t_port Valid integer value between 0 and 65535. 0 = random port, 1-1023 are reserved ports.
         * @param t_addr_type NetworkAddressType enum value. Default is "Any" and resolving t_host will determine type
         */
        ENetSocketNetwork(std::string &t_host, int t_port, NetworkAddressType t_addr_type = NetworkAddressType::Any);

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
         * @brief Determine if the stored IP address and Port are valid
         * @return True if IP address and port are valid else False
         */
        [[nodiscard]] bool is_valid() const;

        /**
         * @brief Return the IP version of the stored IP address
         * @return True if IPv4 address else False
         */
        [[nodiscard]] NetworkAddressType ip_version() const;

        /**
         * @brief Stream overloading
         * @param os Stream handle object
         * @param t Reference to ENetSocketNetwork object
         * @return Return IP address and Port values as a string, delimited by a colon.
         */
        friend std::ostream &operator<<(std::ostream &os, const ENetSocketNetwork &t);

    private:
        void resolve_hostname();

        int make_addr_info();

        std::string m_addr;
        int m_port;

        bool m_valid;
        NetworkAddressType m_addr_type;

        struct addrinfo *m_socket_addrinfo;  // System address info record pointer
    };

}  // End namespace

#endif //ENET_CPP_SOCKET_NET_H
