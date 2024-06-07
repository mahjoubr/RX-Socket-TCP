#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define PORT 8080

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
    pointDeRencontreLocal.sin_port = htons(PORT); // refka : port utilise 8080
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
    sleep(2);
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
