#include "types.h"

// Variables globales
tString historial[MAX_NAMES]; // Para los últimos 5 nombres
int total_repetidos = 0;      
int indice_actual = 0;        
pthread_mutex_t mutex; 

void *handler(void *sock){
    tString nombre_recibido;
    int respuesta;
    int sockCliente = *(int*)sock;
    int esta = FALSE;
    int i = 0;

    // Recibimos el tamaño del paquete y luego el mismo)
    recv(sockCliente, nombre_recibido, NAME_SIZE, 0);

    // Bloqueamos con el mutex y miramos si esta el nombre en el array
    pthread_mutex_lock(&mutex);
    while(!esta && i < MAX_NAMES){
        if(strcmp(nombre_recibido, historial[i])== 0){
            total_repetidos++;
            respuesta = REPE;
            esta = TRUE;
        }
        else{
            respuesta = NO_REPE;
        }
        i++;
    }
    strcpy(historial[indice_actual], nombre_recibido);
    indice_actual = (indice_actual + 1) % MAX_NAMES;
    pthread_mutex_unlock(&mutex);

    // Mostramos la respuesta
    printf("Recibido: %s | Total repetidos históricos: %d\n", nombre_recibido, total_repetidos);
    send(sockCliente, &respuesta, sizeof(int), 0);
    close(sockCliente);
    free(sock);

    return NULL;
}

int main(int argc, char *argv[]){
    int socketfd;
    struct sockaddr_in serverAdderess;
    struct sockaddr_in clientAddress;
    unsigned int port;
    unsigned int clientLength = sizeof(struct sockaddr);

    // Primero comprobamos que no haya fallos al iniciar el server
    if(argc != 2){
        fprintf(stderr, "ERROR\n");
        fprintf(stderr, "Uso: ./server port\n");
        exit(1);
    }

    // Configuracion del servidor
    socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(socketfd < 0){
        perror("ERROR abreindo socket\n");
    }
    memset(&serverAdderess, 0, sizeof(serverAdderess));
    port = atoi(argv[1]);
    serverAdderess.sin_family = AF_INET;
    serverAdderess.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAdderess.sin_port = htons(port);

    // Bind y listen
    if(bind(socketfd, (struct sockaddr*)&serverAdderess, sizeof(serverAdderess)) < 0){
        perror("ERROR haciendo bind");
    }
    listen(socketfd, 10);

    printf("Servidor listo, esperando clientes.\n");

    while(1){
        // Usamos accept para crear un nuevo socket
        int *newSocket = malloc(sizeof(int));
        *newSocket = accept(socketfd, (struct sockaddr *)&clientAddress, &clientLength);
        if(*newSocket < 0){
            perror("ERROR con accept");
        }

        // Creamos el hilo 
        pthread_t thread_ID;
        pthread_create(&thread_ID, NULL, handler, newSocket);
        pthread_detach(thread_ID);
    }

    close(socketfd);
    pthread_mutex_destroy(&mutex);
    return 0;
}