//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
#ifndef ENET_CPP_ADDRESS_H
#define ENET_CPP_ADDRESS_H

#include <string>

namespace enet {

    class ENetSocketAddress {
    public:
        ENetSocketAddress (std::string t_addr, int t_port);

        bool is_valid () const;
        bool is_ipv4 () const;
        bool is_ipv6 () const;
        std::pair<const std::string, const int> get_socket_net () const;

        friend std::ostream& operator<< (std::ostream &os, const ENetSocketAddress& t);

    private:
        std::string m_addr;
        int m_port;
        bool m_valid;
        bool m_ipv4;
        bool m_ipv6;
    };

}

#endif //ENET_CPP_ADDRESS_H
