#include "types.h"


// Variables globales
pthread_mutex_t mutex;
int num_medidas;
tRegistro maximo;
tRegistro minimo;

void *handler(void *sock){
    int clientSocket = *(int*)sock;
    free(sock);
    float medidas[MAX_LENGTH];
    char id[MAX_CHAR];

    // Recibimos los valores
    recv(clientSocket, id, sizeof(char) * MAX_CHAR, 0);
    recv(clientSocket, medidas, sizeof(float) * MAX_LENGTH, 0);

    pthread_mutex_lock(&mutex);

    printf("Received data from sensor %f:", id);
    for(int j = 0; j < MAX_LENGTH; j++){
        printf(" %s ", medidas[j]);
    }

    for(int i = 0; i < MAX_LENGTH; i++){
        if(medidas[i] > maximo.valor){
            maximo.valor = medidas[i];
            strcpy(maximo.ID , id);
        }
        if(medidas[i] < minimo.valor){
            minimo.valor = medidas[i];
            strcpy(minimo.ID , id);
        }

        num_medidas++;
    }

    pthread_mutex_unlock(&mutex);

    printf("Total #value [%f] - MAX[%s: %f] - Min [%s:%f]", num_medidas, maximo.ID, maximo.valor, minimo.ID, minimo.valor);
    // Respondemos con OK
    int respond = OK;
    send(clientSocket, &respond, sizeof(int), 0);

    close(clientSocket);

    return NULL;
}

int main(int argc, char *argv[]){
    int socketfd;
    struct sockaddr_in serverAddres;
    struct sockaddr_in clientAdress;
    int clientLenght = sizeof(struct sockaddr);
    int port;
    
    // Argumentos
    if(argc != 2){
        fprintf(stderr, "ERROR\n");
        fprintf(stderr, "Uso: ./server puerto.\n");
        exit(1);
    }

    socketfd  = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(socketfd < 0){
        perror("Error al crear el socket.");
    }
    memset(&serverAddres, 0, sizeof(serverAddres));
    port = atoi(argv[1]);
    serverAddres.sin_family = AF_INET;
    serverAddres.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddres.sin_port = htons(port);

    // Bind y listen
    if(bind(socketfd, (struct sockaddr*)&serverAddres, sizeof(serverAddres)) < 0){
        perror("ERROR al hacer bind.");
    }
    listen(socketfd, 10);

    printf("El servidor esta correctamnete configurado.\n");

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_lock(&mutex);
    maximo.valor = 0.0;
    minimo.valor = MAX_VALUE;
    pthread_mutex_unlock(&mutex);

    while(1){
        // Accept*
        int *newSocket = malloc(sizeof(int));
        *newSocket = accept(socketfd, (struct sockaddr*)&clientAdress, &clientLenght);
        if(newSocket < 0){
            perror("ERROR aceptando el socket del cliente.");
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