#pragma once
#include "NetworkIncludes.h"

class AddressHandler {
public:
    addrinfo* ResolveAddress(
        std::string host, 
        std::string port
    ) 
    {
       /* Resolve Address */
        addrinfo* result = { nullptr };

        /* Set Protocal Value, Socket Type, and Protocal */
        hints.ai_family         =         AF_UNSPEC  ;
        hints.ai_socktype       =         SOCK_STREAM;
        hints.ai_protocol       =         IPPROTO_TCP;

        /* Get Address Info : Save as a Result */
        int iResult = getaddrinfo(host.c_str(), port.c_str(), GetAddressInfo(), &result);

        if (iResult != 0) 
            return nullptr;

        /* If Result is Valid, return it*/
        return result;
    }

    addrinfo* GetAddressInfo() { return &hints; }

private:
    addrinfo hints{0};
};