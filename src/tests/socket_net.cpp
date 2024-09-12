//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
#include <catch2/catch_test_macros.hpp>
#include "enet_cpp/socket_net.h"
#include "enet_cpp/errors.h"

namespace enet {

    TEST_CASE("Socket network localhost", "[socket-net]") {
        /**
         * Test local host IP addresses
         */
        std::string host = "127.0.0.1";
        auto m_socket_net1 = ENetSocketNetwork(host, 8000, NetworkAddressType::Any);
        REQUIRE(m_socket_net1.is_valid() == true);
        auto [ip1, port1] = m_socket_net1.get_socket_net();
        REQUIRE(ip1 == "127.0.0.1");
        REQUIRE(port1 == 8000);


        host = "::1";
        auto m_socket_net2 = ENetSocketNetwork(host, 8000, NetworkAddressType::Any);
        auto [ip2, port2] = m_socket_net2.get_socket_net();
        REQUIRE(ip2 == "::1");
        REQUIRE(port2 == 8000);

    }

    TEST_CASE("Invalid IP addresses", "[socket-net]") {
        /**
         * Assert invalid IP addresses throw an 'enet_address_info_error' error
         */
        std::string host = "300.0.0.1";
        REQUIRE_THROWS_AS(ENetSocketNetwork(host, 8000, NetworkAddressType::Any), enet_address_info_error);
        host = "2001:db8:a0b:12f0::::0:1";
        REQUIRE_THROWS_AS(ENetSocketNetwork(host, 8000, NetworkAddressType::Any), enet_address_info_error);
    }


} // End namespace