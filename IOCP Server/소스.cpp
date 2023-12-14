#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")

const int MAX_BUFFER_SIZE = 1024;
const int MAX_CLIENTS = 100;

struct ClientContext {
    OVERLAPPED overlapped;
    SOCKET socket;
    char buffer[MAX_BUFFER_SIZE];
    WSABUF dataBuf;
    int dataSize;
};

HANDLE g_completionPort;
SOCKET g_listenSocket;

DWORD WINAPI WorkerThread(LPVOID lpParam) {
    DWORD transferred;
    ULONG_PTR completionKey;
    LPOVERLAPPED overlapped;

    while (true) {
        int result = GetQueuedCompletionStatus(g_completionPort, &transferred, &completionKey, &overlapped, INFINITE);

        if (result == 0 || transferred == 0) {
            // Check if the client intentionally closed the connection
            if (transferred == 0) {
                ClientContext* context = (ClientContext*)overlapped;
                sockaddr_in clientAddr;
                int clientAddrLen = sizeof(clientAddr);
                getpeername(context->socket, (SOCKADDR*)&clientAddr, &clientAddrLen);

                char clientIP[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);

                std::cout << "Client disconnected: " << clientIP << ":" << ntohs(clientAddr.sin_port) << std::endl;
            }

            // Handle errors or disconnections
            closesocket(((ClientContext*)overlapped)->socket);
            delete ((ClientContext*)overlapped);
            continue;
        }

        // Process the received data
        ClientContext* context = (ClientContext*)overlapped;

        if (transferred > 0) {
            // Print the received message to the server log
            context->buffer[transferred] = '\0'; // Null-terminate the received data
            std::cout << "Received from client: " << context->buffer << std::endl;

            // TODO: Handle the received data, e.g., broadcast it to other clients

            // Post another receive operation
            DWORD flags = 0;
            WSARecv(context->socket, &context->dataBuf, 1, NULL, &flags, &context->overlapped, NULL);
        }
    }
}

void CloseServer() {
    closesocket(g_listenSocket);
    CloseHandle(g_completionPort);
}

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock\n";
        return 1;
    }

    // Create the completion port
    g_completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

    // Create a listening socket
    g_listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Bind the socket
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(12345); // Change to your desired port

    bind(g_listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

    // Listen for incoming connections
    listen(g_listenSocket, SOMAXCONN);

    // Create worker threads
    for (int i = 0; i < 4; ++i) {
        HANDLE thread = CreateThread(NULL, 0, WorkerThread, NULL, 0, NULL);
        CloseHandle(thread);
    }

    while (true) {
        // Accept incoming connections and associate them with the completion port
        SOCKET clientSocket = accept(g_listenSocket, NULL, NULL);

        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Failed to accept incoming connection\n";
            continue;
        }

        // Log the connection
        sockaddr_in clientAddr;
        int clientAddrLen = sizeof(clientAddr);
        getpeername(clientSocket, (SOCKADDR*)&clientAddr, &clientAddrLen);

        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);

        std::cout << "Client connected from: " << clientIP << ":" << ntohs(clientAddr.sin_port) << std::endl;

        // Create a context for the client
        ClientContext* context = new ClientContext();
        context->socket = clientSocket;
        context->dataBuf.buf = context->buffer;
        context->dataBuf.len = MAX_BUFFER_SIZE;

        CreateIoCompletionPort((HANDLE)clientSocket, g_completionPort, (ULONG_PTR)context, 0);

        // Post the first receive operation
        DWORD flags = 0;
        WSARecv(clientSocket, &context->dataBuf, 1, NULL, &flags, &context->overlapped, NULL);
    }

    CloseServer();

    return 0;
}
