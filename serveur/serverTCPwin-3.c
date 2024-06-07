#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* pour sleep */
#define PORT 5000
#define LG_MESSAGE 256
int main()
{
WSADATA WSAData; // variable initialisée par WSAStartup
WSAStartup(MAKEWORD(2,0), &WSAData); // indique la version utilisée, ici 2.0
SOCKET socketEcoute;
int iResult;
// Crée un socket de communication
socketEcoute = socket(AF_INET, SOCK_STREAM, 0); /* 0 indique que l’on utilisera le protocole
par défaut associé à SOCK_STREAM soit TCP */
if (socketEcoute == INVALID_SOCKET)
{
printf("Erreur creation socket : %d\n", WSAGetLastError()); WSACleanup();
return 1;
}
// On prépare l’adresse d’attachement locale
struct sockaddr_in pointDeRencontreLocal; // ou SOCKADDR_IN pointDeRencontreLocal;
// Renseigne la structure sockaddr_in avec les informations locales du serveur
pointDeRencontreLocal.sin_family = AF_INET;
pointDeRencontreLocal.sin_addr.s_addr = htonl(INADDR_ANY); // toutes les interfaces locales

// On choisit le numéro de port d’écoute du serveur
pointDeRencontreLocal.sin_port = htons(PORT); // = 5000
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
// On fixe la taille de la file d’attente (pour les demandes de connexion non encore

if (listen(socketEcoute, SOMAXCONN) == SOCKET_ERROR)
{
printf("Erreur listen socket : %d\n", WSAGetLastError());
}
printf("Socket placee en ecoute passive ...\n");
//--- Début de l’étape n°7 :
SOCKET socketDialogue;
struct sockaddr_in pointDeRencontreDistant;
int longueurAdresse = sizeof(pointDeRencontreDistant);
char messageEnvoi[LG_MESSAGE]; /* le message de la couche Application ! */ char
messageRecu[LG_MESSAGE]; /* le message de la couche Application ! */ int
ecrits, lus; /* nb d’octets ecrits et lus */
// boucle d’attente de connexion : en théorie, un serveur attend indéfiniment
while(1)
{
memset(messageEnvoi, 0x00, LG_MESSAGE*sizeof(char));
memset(messageRecu, 0x00, LG_MESSAGE*sizeof(char));
printf("Attente d'une demande de connexion (quitter avec Ctrl-C)\n\n");
// c’est un appel bloquant
socketDialogue = accept(socketEcoute, (SOCKADDR *)&pointDeRencontreDistant, &
longueurAdresse);
if (socketDialogue == INVALID_SOCKET)
{
printf("Erreur accept socket : %d\n", WSAGetLastError()); closesocket(socketEcoute);
WSACleanup();
return 1;
}
// On réception les données du client (cf. protocole !)
// ici appel bloquant
lus = recv(socketDialogue, messageRecu, sizeof(messageRecu), 0); /* attend un message
de TAILLE fixe */
if( lus > 0 ) /* réception de n octets */
printf("Message reçu du client : %s (%d octets)\n\n", messageRecu, lus);
else if ( lus == 0 ) /* la socket est fermée par le serveur */
printf("socket fermé\n");
else /* une erreur ! */
printf("Erreur lecture socket : %d\n", WSAGetLastError());
// On envoie des données vers le client (cf. protocole !)
sprintf(messageEnvoi, "ok\n");
ecrits = send(socketDialogue, messageEnvoi, (int)strlen(messageEnvoi), 0); // message à

if (ecrits == SOCKET_ERROR)
{
printf("Erreur envoi socket : %d\n", WSAGetLastError()); closesocket(socketDialogue);
WSACleanup();
return 1;
}
printf("Message %s envoye (%d octets)\n\n", messageEnvoi, ecrits);
// On ferme la socket de dialogue et on se replace en attente ...
closesocket(socketDialogue);
}
//--- Fin de l’étape n°7 !
// On ferme la ressource avant de quitter
iResult = closesocket(socketEcoute);
if (iResult == SOCKET_ERROR)
{
printf("Erreur fermeture socket : %d\n", WSAGetLastError());
WSACleanup();
return 1;
}
WSACleanup(); // termine l’utilisation
return 0;
}

