//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
#ifndef ENET_CPP_ERRORS_H
#define ENET_CPP_ERRORS_H

#include <stdexcept>

namespace enet {

    class enet_address_info_error : public std::runtime_error {
        /**
        * Invalid socket info error - an invalid IP Address or Port
        */
    public:
        explicit enet_address_info_error(const std::string &t_err_msg) : std::runtime_error(t_err_msg) {}
    };

    class enet_socket_error : public std::runtime_error {
        /**
        * Socket error - an error occurred while opening or using a socket
        */
    public:
        explicit enet_socket_error(const std::string &t_err_msg) : std::runtime_error(t_err_msg) {}
    };

}

#endif //ENET_CPP_ERRORS_H
