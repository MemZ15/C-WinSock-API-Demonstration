#include "NetworkIncludes.h"
#include "NetworkHandler.h"

void NetworkHandler::CreateServer()
{
    /* Create listening socket */
    SOCKET listenSocket = CreateSocket();

    /* Create server address information */
    sockaddr_in serverInfo = CreateServerInformation(0);

    /* Bind to local address and start listening */
    BindSocketAndListen(listenSocket, serverInfo);

    printf("[+] Server listening on port 8080...\n");

    /* Start worker thread to manage clients */
    ManageIncomingClients(listenSocket);

}

void NetworkHandler::ManageIncomingClients
(
    SOCKET 
    listeningSocket
)
{
    while (ServerRunning)
    {
        /* Create New Client Address Object */
        sockaddr_in clientAddr{};
        int clientSize{ sizeof(sockaddr_in) };

        /* CreateClientAcceptorSocket */
        SOCKET clientSocket = accept(
            listeningSocket,
            reinterpret_cast<sockaddr*>(&clientAddr),
            &clientSize
        );

        /* Check if server is still running before handling client */ 
        if (!ServerRunning)
            break;

        /* Check if client socket is valid */
        if (clientSocket == INVALID_SOCKET)
        {
            int error = WSAGetLastError();
            printf("[-] accept() failed (%d)\n", error);
            continue;
        }

        /* GetClientSession Object and Prepare its Socket and Address for the owning Client Object */
        auto ClientSession = GetSessionHandler()->PrepareSocketAndAddress(
            clientAddr, 
            clientSocket, 
            clientAddr
        );

        /* Create and Dispatch Async Thread to handle Client Connections. */
        std::thread(
            &NetworkHandler::OnClientConnect,
            this,
            clientSocket,
            ClientSession
        ).detach();
    }

    printf("[-] Accept Connection thread terminated\n");
}


void NetworkHandler::OnClientConnect
(
    SOCKET clientSocket, 
    SessionHandler::ClientSession Session
)
{
    auto& Self = NetworkHandler::GetInstance();

    printf("[+] Client connected [%s:%u]\n",
           Session.Ip.c_str(),
           Session.Port
    );

    char buffer[4096]{ 0 };

    int bytes = recv(clientSocket, buffer, sizeof(buffer), 0);

    if (bytes <= 0)
    {
        closesocket(clientSocket);
        return;
    }

    HttpRequest req = Self.GetResponseBuilder()->ParseHTTPRequest(buffer, bytes);

    /* TODO : Call Handler*/

    auto ToSend =
        Self.GetResponseBuilder()->Build(200, "OK", "Hello World");

    send(clientSocket, ToSend.data(), (int)ToSend.size(), 0);

    std::printf("[+] Response Sent!\n");
}

bool NetworkHandler::InitializeWinsock() 
{
    if (m_initialized) return true;

    /* Call WSA Startup */
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != 0)
        return false;

    m_initialized = true;
    return true;
}

sockaddr_in NetworkHandler::CreateServerInformation
(
    USHORT Port
) 
{
    /* Create Server Typing Information*/
    sockaddr_in serverAddr{};
    
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    return serverAddr;
}

SOCKET NetworkHandler::CreateSocket() 
{
    /* Create Listener Socket */
    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listenSocket == INVALID_SOCKET) 
    {
        printf("socket() failed: %ld\n", WSAGetLastError());
        WSACleanup();
        return INVALID_SOCKET;
    }

    ServerRunning = true;
    return listenSocket;
}

bool NetworkHandler::BindSocketAndListen(
    SOCKET sock, 
    sockaddr_in addr
)
{
    /* Bind Socket and Address */
    if (bind(sock, (sockaddr*)&addr, sizeof(sockaddr)) == SOCKET_ERROR)
    {
        printf("bind() failed: %ld\n", WSAGetLastError());
        return false;
    }

    /* Listen on binded socket @ the provided Address */
    if (listen(sock, SOMAXCONN) == SOCKET_ERROR)
    {
        printf("listen() failed: %ld\n", WSAGetLastError());
        return false;
    }

    return true;
}