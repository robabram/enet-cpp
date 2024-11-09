//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
#include <catch2/catch_test_macros.hpp>
#include "enet_cpp/enet.h"

namespace enet {

    TEST_CASE("Simple host", "[host]") {
        /**
         * Test local host IP addresses
         */
        std::string network = "127.0.0.1";
        auto m_socket_net = ENetSocketNetwork(network, 8000);

        ENetHost host = ENetHost(network, 8000, NetworkAddressType::IPv4);
    }
}