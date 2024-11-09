//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//

#ifndef ENET_CPP_ENUMS_H
#define ENET_CPP_ENUMS_H

namespace enet {

    /**
     * Indicates the either a choice of IP version to use or what IP version is in use.
     */
    enum class NetworkAddressType {
        Any, IPv4, IPv6
    };

} // End namespace

#endif //ENET_CPP_ENUMS_H
