#include <stdio.h> 
#include <pthread.h> 
#include <ctype.h> 
#include <stdlib.h> 
#include <string.h> 
#include <time.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/stat.h> 
#include <arpa/inet.h> 
#include <fcntl.h> 
 
// True 
#define TRUE 1 
 
// False 
#define FALSE 0 
 
// Connection successful 
#define OK 12345 
 
// Maximum number of elements 
#define MAX_LENGTH 10 
 
// Maximum number of chars 
#define MAX_CHAR 16  
 
// Maximum value 
#define MAX_VALUE 300.0 

typedef struct{
    float valor;
    char ID[MAX_CHAR];
}tRegistro;