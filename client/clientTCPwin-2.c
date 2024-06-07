#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

#define PORT 8081



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
    struct sockaddr_in pointDeRencontreDistant;
    pointDeRencontreDistant.sin_family = AF_INET;
    pointDeRencontreDistant.sin_addr.s_addr = inet_addr("127.0.0.1");
    pointDeRencontreDistant.sin_port = htons(PORT); // refka: port utilise 8081
    iResult = connect(descripteurSocket, (SOCKADDR *)&pointDeRencontreDistant, sizeof(pointDeRencontreDistant));
    if (iResult == SOCKET_ERROR)
    {
        printf("Erreur connexion socket : %d\n", WSAGetLastError());
        iResult = closesocket(descripteurSocket);
        if (iResult == SOCKET_ERROR)
        {
            printf("Erreur fermeture socket : %d\n", WSAGetLastError());
        }
        WSACleanup();
        return 1;
    }
    printf("Connexion au serveur reussie avec succes !\n");
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
