#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "ws2_32.lib")
int main()
{
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    SOCKET descripteurSocket;
    int iResult;
    descripteurSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (descripteurSocket == INVALID_SOCKET)
    {
        printf("Erreur creation socket : %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    printf("Socket cree avec succes !\n");
    iResult = closesocket(descripteurSocket);
    if (iResult == SOCKET_ERROR)
    {
        printf("Erreur fermeture socket : %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    WSACleanup();
    return 0;
}
