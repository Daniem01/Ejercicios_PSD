#include "types.h"

int main(int argc, char *argv[]){
    int socketfd;
    unsigned int port;
    struct sockaddr_in serverAddress;
    char *serverIp;
    tString nombre;
    strcpy(nombre, argv[3]);
    int repetido;

    // Comprobamos que los atributos son el numero correcto
    if(argc != 4){
        fprintf(stderr, "ERROR\n");
        fprintf(stderr, "USO: ./client serverIP serverPort name\n");
        exit(1);
    }

    serverIp = argv[1];
    port = atoi(argv[2]);
    strcpy(nombre, argv[3]);

    // Creamos el socket
    socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(socketfd < 0 ){
        perror("ERROR creando el socket.");
    }

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(serverIp);
    serverAddress.sin_port = htons(port);

    // Conectar al servidor
    if(connect(socketfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0){
        perror("ERROR conectandose al servidor\n");
    }

    // Mandamos el nombre y recibimos si esta repetido o no
    send(socketfd, nombre, NAME_SIZE, 0);
    recv(socketfd, &repetido, sizeof(int), 0);
    if(repetido == REPE){
        printf("El nombre %s estaba repetido.\n", nombre);
    }
    else{
        printf("El nombre %s no estaba repetido.\n", nombre);
    }

    close(socketfd);
    return 0;
}