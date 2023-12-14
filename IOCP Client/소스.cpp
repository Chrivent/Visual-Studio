#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

const int MAX_BUFFER_SIZE = 1024;

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock\n";
        return 1;
    }

    // Create a socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket\n";
        WSACleanup();
        return 1;
    }

    // Connect to the server
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) != 1) {
        std::cerr << "Invalid address\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    serverAddr.sin_port = htons(12345); // Change to your server's port

    if (connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to server\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // Send and receive data
    char buffer[MAX_BUFFER_SIZE];
    while (true) {
        // Send a message to the server
        std::cout << "Enter a message to send (or 'exit' to quit): ";
        std::cin.getline(buffer, MAX_BUFFER_SIZE);

        if (_stricmp(buffer, "exit") == 0) {
            break;
        }

        send(clientSocket, buffer, strlen(buffer), 0);

        // Receive the response from the server
        int bytesReceived = recv(clientSocket, buffer, MAX_BUFFER_SIZE, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::cout << "Server says: " << buffer << std::endl;
        }
    }

    // Clean up
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
