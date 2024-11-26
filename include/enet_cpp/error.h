//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//
#ifndef ENET_CPP_ERROR_H
#define ENET_CPP_ERROR_H

#include <source_location>
#include <iostream>
#include <format>
#include <stdexcept>

namespace enet {

    /**
     * @brief Enumeration of possible behaviors for the Expect() function. Based on sample
     *        code for an "expect()" function from Bjarne Stroustrup.
     *
     *        ignore : Do nothing, expect() statements will not be included in compiled binary
     *        throwing : Failed condition call will throw exception
     *        terminating : Failed condition will terminate program
     *        logging : Failed condition will log message to std::cerr
     */
    enum class ErrorActionEnum { ignore, throwing, terminating, logging };

    /**
     * @brief Default behavior for the Expect() function. Change this default to change
     *        behavior of the expect() function. Setting default to "ignore" will cause
     *        the expect() function calls to be removed from the compiled binary.
     *        Note: This is a compile time setting and should not be changed to a runtime setting.
     */
    constexpr ErrorActionEnum default_error_action = ErrorActionEnum::logging;

    /* ------------------------------------------------------------------------------------
     * Predefined exception classes
     * -----------------------------------------------------------------------------------*/

    /**
    * @brief Exception: Invalid socket info error, an invalid IP address or port.
    */
    class AddressInfoError : public std::runtime_error {
    public:
        const std::string m_error = "Invalid socket info error, an invalid IP address or port";
        explicit AddressInfoError(const std::string &t_err_msg = std::string()) :
                std::runtime_error(!t_err_msg.empty() ? t_err_msg : m_error) {}
    };

    /**
    * @brief Exception: Socket error, an error occurred while opening or using a socket.
    */
    class SocketError : public std::runtime_error {
    public:
        const std::string m_error = "Socket error, an error occurred while opening or using a socket";
        explicit SocketError(const std::string &t_err_msg = std::string()) :
                std::runtime_error(!t_err_msg.empty() ? t_err_msg : m_error) {}
    };

    /* ------------------------------------------------------------------------------------
     * End Predefined exception classes
     * -----------------------------------------------------------------------------------*/

    /**
     * @brief Expect function for testing invariants, pre-existing conditions, etc.
     *        Take "action" if the expected condition "cond" doesn't hold.
     */
    template<ErrorActionEnum action = default_error_action, class C>
    constexpr void expect(C cond, const std::runtime_error &ex,
                          std::source_location loc = std::source_location::current()) {
        if constexpr (action == ErrorActionEnum::logging)
            if (!cond()) {
                std::string msg = std::format("{} ({}:{}): {}", loc.file_name(), loc.line(), loc.column(), ex.what());
                std::cerr << "expect() failure: " << msg << '\n';
            }
        if constexpr (action == ErrorActionEnum::throwing)
            if (!cond()) throw ex;
        if constexpr (action == ErrorActionEnum::terminating)
            if (!cond()) std::terminate();
        // or no action
    }
}

#endif //ENET_CPP_ERROR_H
