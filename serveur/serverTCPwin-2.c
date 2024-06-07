#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define PORT 8081

int main()
{
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    SOCKET socketEcoute;
    int iResult;

    socketEcoute = socket(AF_INET, SOCK_STREAM, 0);

    if (socketEcoute == INVALID_SOCKET)
    {
        printf("Erreur creation socket : %d\n", WSAGetLastError()); WSACleanup();
        return 1;
    }
    struct sockaddr_in pointDeRencontreLocal;
    pointDeRencontreLocal.sin_family = AF_INET;
    pointDeRencontreLocal.sin_addr.s_addr = htonl(INADDR_ANY);
    pointDeRencontreLocal.sin_port = htons(PORT);//port que j'ai utilise 8081 refka
    iResult = bind(socketEcoute, (SOCKADDR *)&pointDeRencontreLocal, sizeof(
    pointDeRencontreLocal));
    if (iResult == SOCKET_ERROR)
    {
        printf("Erreur bind socket : %d\n", WSAGetLastError());
        closesocket(socketEcoute);
        WSACleanup();
        return 1;
    }
    printf("Socket attachee avec succes !\n");
    if (listen(socketEcoute, SOMAXCONN) == SOCKET_ERROR)
    {
        printf("Erreur listen socket : %d\n", WSAGetLastError());
    }
    iResult = closesocket(socketEcoute);
    if (iResult == SOCKET_ERROR)
    {
        printf("Erreur fermeture socket : %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    WSACleanup();
    return 0;
}
