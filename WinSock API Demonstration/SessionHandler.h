#pragma once
#include "NetworkIncludes.h"
#include "NetworkHandler.h"
#include "ResponseBuilder.h"
#include <functional>
#include <mutex>

class SessionHandler {
public:
    using Handler = std::function<std::string(HttpRequest)>;

    struct ClientSession
    {
        SOCKET Socket{};
        sockaddr_in Address{};

        std::string Ip{};
        uint16_t Port{};

        bool Connected{ true };
    };

    ClientSession PrepareSocketAndAddress(sockaddr_in IncomingClient, SOCKET socket, sockaddr_in Address) {
        ClientSession ctx{};
        ctx.Address = Address;
        ctx.Socket = socket;

        char ipBuffer[INET_ADDRSTRLEN]{};

        inet_ntop(AF_INET, &IncomingClient.sin_addr, ipBuffer, sizeof(ipBuffer));

        ctx.Ip = ipBuffer;
        ctx.Port = ntohs(IncomingClient.sin_port);

        return ctx;
    }

private:
};