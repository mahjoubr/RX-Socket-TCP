#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#define PORT 5000
#define LG_MESSAGE 256
int main()
{
WSADATA WSAData; // variable initialisée par WSAStartup
WSAStartup(MAKEWORD(2,0), &WSAData); // indique la version utilisée, ici 2.0 SOCKET
SOCKET descripteurSocket;
int iResult;
// Crée un socket de communication
descripteurSocket = socket(AF_INET, SOCK_STREAM, 0); /* 0 indique que l’on utilisera le
protocole par défaut associé à SOCK_STREAM soit TCP */
if (descripteurSocket == INVALID_SOCKET)
{
printf("Erreur creation socket : %d\n", WSAGetLastError()); WSACleanup();
return 1;
}
struct sockaddr_in pointDeRencontreDistant; // ou SOCKADDR_IN pointDeRencontreDistant;
// Renseigne la structure sockaddr_in avec les informations du serveur distant
pointDeRencontreDistant.sin_family = AF_INET;
// On choisit l’adresse IPv4 du serveur
pointDeRencontreDistant.sin_addr.s_addr = inet_addr("192.168.56.1"); // à modifier selon ses besoins

// On choisit le numéro de port d’écoute du serveur
pointDeRencontreDistant.sin_port = htons(PORT); // = 5000
// Débute la connexion vers le processus serveur distant
iResult = connect(descripteurSocket, (SOCKADDR *)&pointDeRencontreDistant, sizeof(pointDeRencontreDistant));
if (iResult == SOCKET_ERROR)
{
printf("Erreur connexion socket : %d\n", WSAGetLastError());
iResult = closesocket(descripteurSocket); // On ferme la ressource avant de quitter
if
(iResult == SOCKET_ERROR)
{
printf("Erreur fermeture socket : %d\n", WSAGetLastError());
}
WSACleanup();
return 1; // On sort en indiquant un code erreur
}
printf("Connexion au serveur refka reussie avec succes !\n");
//--- Début de l’étape n°4 :
char messageEnvoi[LG_MESSAGE]; /* le message de la couche Application ! */
char
messageRecu[LG_MESSAGE]; /* le message de la couche Application ! */
int ecrits, lus; /* nb d’octets ecrits et lus */
sprintf(messageEnvoi, "Hello refka !\n");
ecrits = send(descripteurSocket, messageEnvoi, (int)strlen(messageEnvoi), 0);

if (ecrits == SOCKET_ERROR)
{
printf("Erreur envoi socket : %d\n", WSAGetLastError());
closesocket(descripteurSocket);
WSACleanup();
return 1;
}
printf("Message %s envoye avec succes (%d octets)\n\n", messageEnvoi, ecrits);
/* Reception des données du serveur */
lus = recv(descripteurSocket, messageRecu, sizeof(messageRecu), 0); /* attend un message de
TAILLE fixe */
if( lus > 0 ) /* réception de n octets */
printf("Message reçu du serveur : %s (%d octets)\n\n", messageRecu, lus);
else if ( lus == 0 ) /* la socket est fermée par le serveur */
printf("La socket a été fermée par le serveur !\n");
else /* une erreur ! */
printf("Erreur lecture socket : %d\n", WSAGetLastError());
//--- Fin de l’étape n°4 !
// On ferme la ressource avant de quitter
iResult = closesocket(descripteurSocket);
if (iResult == SOCKET_ERROR)
{
printf("Erreur fermeture socket : %d\n", WSAGetLastError()); WSACleanup();
return 1;
}
WSACleanup(); // termine l’utilisation
return 0;
}

