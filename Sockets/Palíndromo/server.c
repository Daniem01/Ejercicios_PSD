#include "types.h"

int es_Palindromo(tString palabra, int tam){
    tString reves;
    int j = 0;
    
    for(int i = tam - 1; i >= 0; i--){
        reves[j] = palabra[i];
        j++;
    }

    reves[tam] = '\0';
    if(strcmp(reves, palabra) == 0){
        return ESPALIN;
    }
    else{
        return NOESPALIN;
    }
}

void *handler(void *sock){
    int tamaño_palabra;
    tString palabra;
    int socketCliente = *(int*)sock;
    free(sock);
    int palindromo;

    // Recibimos el tamaño y la palabra
    recv(socketCliente, &tamaño_palabra, sizeof(int), 0);
    recv(socketCliente, palabra, tamaño_palabra, 0);

    palindromo = es_Palindromo(palabra, tamaño_palabra);

    send(socketCliente, &palindromo, sizeof(int), 0);

    close(socketCliente);

    return NULL;
}

int main(int argc, char *argv[]){
    int socketfd;
    struct sockaddr_in serverAdress;
    struct sockaddr_in clientAdress;
    unsigned int port;
    unsigned int clientLenght = sizeof(struct sockaddr);

    if(argc != 2){
        fprintf(stderr, "ERROR\n");
        fprintf(stderr, "Uso: ./server port\n");
        exit(1);
    }

    // Configuracion del socket
    socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(socketfd < 0){
        perror("ERROR creando el socket.");
    }
    memset(&serverAdress, 0, sizeof(serverAdress));
    port = atoi(argv[1]);
    serverAdress.sin_family = AF_INET;
    serverAdress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAdress.sin_port = htons(port);

    // Bind y listen
    if(bind(socketfd, (struct sockaddr*)&serverAdress, sizeof(serverAdress)) < 0){
        perror("ERROR en el bind");
    }
    listen(socketfd, 1);

    printf("Servidor listo y esperando.\n");

    // Escucha
    while(1){
        // Acepta a los clientes
        int *newSocket = malloc(sizeof(int));
        *newSocket = accept(socketfd, (struct sockaddr*)&clientAdress, &clientLenght);
        if(newSocket < 0){
            perror("ERROR creando el socket del cliente.");
        }

        pthread_t thread_ID;
        pthread_create(&thread_ID, NULL, handler, newSocket);
        pthread_detach(thread_ID);
    }

    close(socketfd);

    return 0;
}