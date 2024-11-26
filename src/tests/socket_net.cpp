//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
#include <catch2/catch_test_macros.hpp>
#include "enet_cpp/enet.h"
#include "enet_cpp/error.h"

namespace enet {

    TEST_CASE("Socket network localhost", "[socket-net]") {
        /**
         * Test local host IP addresses
         */
        // Default action for expect() calls must be set to "throwing" for tests to work correctly.
        REQUIRE(default_error_action == ErrorActionEnum::throwing);

        std::string host = "127.0.0.1";
        auto m_socket_net1 = ENetSocketNetwork(host, 8000);
        REQUIRE(m_socket_net1.is_valid() == true);
        auto [ip1, port1] = m_socket_net1.get_socket_net();
        REQUIRE(ip1 == "127.0.0.1");
        REQUIRE(port1 == 8000);

        host = "::1";
        auto m_socket_net2 = ENetSocketNetwork(host, 8000, NetworkAddressType::IPv6);
        auto [ip2, port2] = m_socket_net2.get_socket_net();
        REQUIRE(ip2 == "::1");
        REQUIRE(port2 == 8000);

        // Test with no host var
        auto m_socket_net3 = ENetSocketNetwork("10.0.0.1", 8000, NetworkAddressType::IPv4);
        auto [ip3, port3] = m_socket_net3.get_socket_net();
        REQUIRE(ip3 == "10.0.0.1");
        REQUIRE(port3 == 8000);
    }

    TEST_CASE("Invalid IP addresses", "[socket-net]") {
        /**
         * Assert invalid IP addresses throw an 'AddressInfoError' error
         */
        // Default action for expect() calls must be set to "throwing" for tests to work correctly.
        REQUIRE(default_error_action == ErrorActionEnum::throwing);

        std::string host = "300.0.0.1";
        REQUIRE_THROWS_AS(ENetSocketNetwork(host, 8000, NetworkAddressType::Any), AddressInfoError);
        host = "2001:db8:a0b:12f0::::0:1";
        REQUIRE_THROWS_AS(ENetSocketNetwork(host, 8000, NetworkAddressType::Any), AddressInfoError);
    }

    TEST_CASE("IP address becomes a copy", "[socket-net]") {
        /**
         * Ensure that the IP address we pass to ENetSocketNetwork becomes a copy
         */
        std::string host = "127.0.0.1";
        auto m_socket_net1 = ENetSocketNetwork(host, 8000, NetworkAddressType::Any);
        auto [ip, port] = m_socket_net1.get_socket_net();
        REQUIRE(host == "127.0.0.1");
        REQUIRE(host == ip);
        REQUIRE(host.c_str() != ip.c_str());
    }


} // End namespace