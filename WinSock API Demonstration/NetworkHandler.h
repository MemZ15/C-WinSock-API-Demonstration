#pragma once
#include "NetworkIncludes.h"
#include "AddressHandler.h"
#include "SessionHandler.h"
#include "ResponseBuilder.h"

class NetworkHandler {
public:
    ~NetworkHandler() {
        free(m_SessionHandler);
        free(addressHandler);
        free(m_ResponseBuilder);
        WSACleanup();
    };

    static NetworkHandler& GetInstance() { return instance; }

    AddressHandler* GetAddressHandler() { return addressHandler; }

    SessionHandler* GetSessionHandler() { return m_SessionHandler; }

    ResponseBuilder* GetResponseBuilder() { return m_ResponseBuilder; }

    void CreateServer();

    bool InitializeWinsock();

private:
    bool BindSocketAndListen(SOCKET sock, sockaddr_in addr);

    void ManageIncomingClients(SOCKET listeningSocket);

    void OnClientConnect(SOCKET clientSocket, SessionHandler::ClientSession Session);

    sockaddr_in CreateServerInformation(USHORT Port);

    SOCKET CreateSocket();

private:
    WSADATA wsaData{};
    bool m_initialized{ false };
    static NetworkHandler instance;
    std::atomic_bool ServerRunning{ false };
    SessionHandler* m_SessionHandler = { nullptr };
    AddressHandler* addressHandler = {nullptr};
    ResponseBuilder* m_ResponseBuilder = { nullptr };
};