//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
#include <cstring>
#include <format>
#include <regex>
#include <iostream>
#include "enet_cpp/errors.h"
#include "enet_cpp/socket_net.h"


namespace enet {

    ENetSocketNetwork::ENetSocketNetwork(std::string t_addr, int t_port) :
            m_addr{std::move(t_addr)},
            m_port{t_port},
            m_valid{false},
            m_ipv4{false},
            m_ipv6{false},
            m_socket_addrinfo{nullptr} {
        // IPv4 regex expression
        std::regex r_ipv4(
                "(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
        // IPv6 regex expression
        std::regex ipv6("((([0-9a-fA-F]){1,4})\\:){7}([0-9a-fA-F]){1,4}");

        // Validate that we have an IPv4 address or an IPv6 address
        if (std::regex_match(m_addr, r_ipv4))  { m_ipv4 = true; }
        else if (std::regex_match(m_addr, ipv6)) { m_ipv6 = true; }

        // Check port, range is: 0 -> 65535
        if ((m_ipv4 || m_ipv6) && m_port >= 0 && m_port <= 65535) { m_valid = true; }

        if (m_valid) {
            make_addr_info();
        } else {
            std::string msg = std::format("Invalid socket address: {}:{}", m_addr, m_port);
            throw enet_address_info_error(msg);
        }
    }

    ENetSocketNetwork::~ENetSocketNetwork() {
        if (m_socket_addrinfo != nullptr) {
            std::cout << "Freeing address info record" << "\n";
            freeaddrinfo(m_socket_addrinfo);
            m_socket_addrinfo = nullptr;
        }
    }

    addrinfo *ENetSocketNetwork::get_addrinfo_rec() const {
        return m_socket_addrinfo;
    }

    std::pair<const std::string, int> ENetSocketNetwork::get_socket_net() const {
        return {m_addr, m_port};
    }

    bool ENetSocketNetwork::is_valid() const { return m_valid; }

    bool ENetSocketNetwork::is_ipv4() const { return m_ipv4; }

    bool ENetSocketNetwork::is_ipv6() const { return m_ipv6; }

    std::ostream &operator<<(std::ostream &os, const ENetSocketNetwork &t) {
        return os << std::format("{}:{}", t.m_addr, t.m_port);
    }

    void ENetSocketNetwork::make_addr_info() {
        /**
         * Construct the socket address info record for use with a socket.
         */
        struct addrinfo hints{};
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_protocol = IPPROTO_UDP;

        std::string s_port = std::to_string(m_port);
        int result = getaddrinfo(m_addr.c_str(), s_port.c_str(), &hints, &m_socket_addrinfo);

        if (result != 0 || m_socket_addrinfo == nullptr) {
            std::string msg = std::format("Invalid address or port: {}:{}", m_addr, m_port);
            throw enet_address_info_error(msg);
        }
    }

} // End namespace