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

// Code for a repeated name 
#define REPE 123  

// Code for a non-repeated name 
#define NO_REPE 456  

// Maximum number of names 
#define MAX_NAMES 5  

// Name length 
#define NAME_SIZE 128  

// Type for names 
typedef char tString [NAME_SIZE];