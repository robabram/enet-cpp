//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
#include <cstring>
#include <format>
#include <random>
#include <regex>
#include <iostream>

#include "enet_cpp/error.h"
#include "enet_cpp/socket_net.h"


namespace enet {

    ENetSocketNetwork::ENetSocketNetwork(const std::string& t_host, int t_port, NetworkAddressType t_addr_type) :
            m_addr{t_host},
            m_port{t_port},
            m_valid{true},
            m_addr_type{t_addr_type},
            m_socket_addrinfo{nullptr}
    {
        // IPv4 regex expression
        const std::regex r_ipv4(
                "(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
        // IPv6 regex expression
        const std::regex ipv6("((([0-9a-fA-F]){1,4})\\:){7}([0-9a-fA-F]){1,4}");

        // Validate that we have an IPv4 address or an IPv6 address
        if (std::regex_match(m_addr, r_ipv4))  {
            m_addr_type = NetworkAddressType::IPv4;
        } else {
            if (std::regex_match(m_addr, ipv6)) {
                m_addr_type = NetworkAddressType::IPv6;
            } else {
                m_valid = resolve_hostname();
            }
        }

        // Check port, valid range is between 1 and 65535.
        expect([this] { return this->m_port >= 0 && this->m_port < 65536; },
               std::range_error("Socket port number out of range"));
        if (m_port == 0) {
            // Seed with a real random value, if available
            std::random_device r;
            std::default_random_engine gen(r());
            std::uniform_int_distribution<int> distribution(2048,65535);
            m_port = distribution(gen);
        }
    }

    ENetSocketNetwork::~ENetSocketNetwork() {
        if (m_socket_addrinfo != nullptr) {
            std::cout << "Freeing address info record" << "\n";
            freeaddrinfo(m_socket_addrinfo);
            m_socket_addrinfo = nullptr;
        }
    }

    void ENetSocketNetwork::initialize() {
        /**
         * Initialize the socket address info record for use with a socket.
         */
        struct addrinfo hints{};
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_protocol = IPPROTO_UDP;

        std::string s_port = std::to_string(m_port);
        auto result = getaddrinfo(m_addr.c_str(), s_port.c_str(), &hints, &m_socket_addrinfo);
        m_valid = (result == 0 && m_socket_addrinfo != nullptr);

        expect([this] { return this->m_valid; }, AddressInfoError(
                std::format("Invalid socket address: {}:{} ({})", m_addr, m_port, result)));
    }

    addrinfo *ENetSocketNetwork::get_addrinfo_rec() const {
        return m_socket_addrinfo;
    }

    std::pair<const std::string, int> ENetSocketNetwork::get_socket_net() const {
        return {m_addr, m_port};
    }

    bool ENetSocketNetwork::is_valid() const { return m_valid; }

    NetworkAddressType ENetSocketNetwork::ip_version() const { return m_addr_type; }

    std::ostream &operator<<(std::ostream &os, const ENetSocketNetwork &t) {
        return os << std::format("{}:{}", t.m_addr, t.m_port);
    }

    bool ENetSocketNetwork::resolve_hostname() {
        /**
         * Attempt to resolve the hostname to an IP address by making a DNS request
         */
        struct addrinfo hints{};
        int status;
        void *addr_ptr;
        char addr_buf[INET6_ADDRSTRLEN];
        struct addrinfo *tmp_addrinfo = nullptr;

        // Initialize hints structure using requested IP address type
        memset(&hints, 0, sizeof(hints));
        hints.ai_socktype = SOCK_STREAM;
        switch (m_addr_type) {
            case (NetworkAddressType::IPv4) : { hints.ai_family = AF_INET; break; }
            case (NetworkAddressType::IPv6) : { hints.ai_family = AF_INET6; break; }
            default: { hints.ai_family = AF_UNSPEC; }
        }

        // Resolve the hostname to an IP address
        status = getaddrinfo(m_addr.c_str(), nullptr, &hints, &tmp_addrinfo);

        expect([status] { return status == 0; },
            AddressInfoError(std::format("Failed to resolve hostname: {} ({})", m_addr, status)));

        if (status != 0)
            return false;

        // The output of a DNS request may contain multiple IP addresses, but we will only use the first one.
        if (tmp_addrinfo->ai_family == AF_INET) { // Address is IPv4
            addr_ptr = &(reinterpret_cast<struct sockaddr_in*>(tmp_addrinfo->ai_addr)->sin_addr);
            m_addr_type = NetworkAddressType::IPv4;
        } else {  // Address is IPv6
            addr_ptr = &(reinterpret_cast<struct sockaddr_in6*>(tmp_addrinfo->ai_addr)->sin6_addr);
            m_addr_type = NetworkAddressType::IPv6;
        }

        m_addr = inet_ntop(tmp_addrinfo->ai_addr->sa_family, addr_ptr, addr_buf, sizeof(addr_buf));
        freeaddrinfo(tmp_addrinfo);
        return true;
    }

} // End namespace