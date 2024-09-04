//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
#include <format>
#include <regex>
#include "enet_cpp/errors.h"
#include "enet_cpp/address.h"

namespace enet {

    ENetSocketAddress::ENetSocketAddress(std::string t_addr, int t_port) :
            m_addr{std::move(t_addr)},
            m_port{t_port},
            m_valid{false},
            m_ipv4{false},
            m_ipv6{false} {
        // IPv4 regex expression
        std::regex r_ipv4(
                "(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");

        // IPv6 regex expression
        std::regex ipv6("((([0-9a-fA-F]){1,4})\\:){7}([0-9a-fA-F]){1,4}");

        // Validate that we have an IPv4 address or an IPv6 address
        if (std::regex_match(m_addr, r_ipv4)) {
            m_ipv4 = true;
        } else {
            if (std::regex_match(m_addr, ipv6)) {
                m_ipv6 = true;
            }
        }

        // Check port, range is: 0 -> 65535
        if ((m_ipv4 || m_ipv6) && m_port >= 0 && m_port <= 65535) {
            m_valid = true;
            return;
        }

        std::string msg = std::format("Invalid socket address: {}:{}", m_addr, m_port);
        throw enet_address_error(msg);

    }

    bool ENetSocketAddress::is_valid() { return m_valid; }

    bool ENetSocketAddress::is_ipv4() { return m_ipv4; }

    bool ENetSocketAddress::is_ipv6() { return m_ipv6; }

    std::pair<const std::string, const int> ENetSocketAddress::get_socket_net() {
        return {m_addr, m_port};
    }

    std::ostream &operator<< (std::ostream &os, const ENetSocketAddress& t) {
        return os << std::format("{}:{}", t.m_addr, t.m_port);
    }

}