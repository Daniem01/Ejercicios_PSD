#include <stdio.h> 
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
#include <pthread.h>
 
/** Length for tString */ 
#define STRING_LENGTH 128 
 
/** Type for names, messages and this kind of variables */ 
typedef char tString [STRING_LENGTH]; 
 
/** True value */ 
#define TRUE 1 
 
/** False value */ 
#define FALSE 0 
 
// Codes 
#define ESPALIN 111 
#define NOESPALIN 222 