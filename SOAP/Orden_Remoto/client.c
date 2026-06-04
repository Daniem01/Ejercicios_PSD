#include <stdio.h>
#include <stdlib.h>
#include "soapH.h"           
#include "ordenRemoto.nsmap"
#include <string.h>

unsigned int* createVector (int length){ 
 
    unsigned int * vector = (unsigned int *) malloc (length * sizeof (unsigned int)); 
  
    for (int i=0; i<length; i++) 
        vector[i] = rand() % MAX_VALUE;  
   
    return vector; 
} 
 
void showVector (unsigned int * vector, int length){ 
   
    printf ("Vector: "); 
   
    for (int i=0; i<length; i++) 
        printf ("%u ", vector[i]); 
   
    printf ("\n"); 
} 
 
 
int main(int argc, char **argv){ 
    ordenRemoto_ns__tVector mi_vector;
    mi_vector.__size = MAX_VECTOR_SIZE;
    int result; 
    ordenRemoto_ns__tVector vector; 
    struct soap soap;

    if(argc != 3){
        printf("Uso: %s <URL> <operation>\n", argv[0]);
        exit(1);
    }

    mi_vector.__ptr = createVector(MAX_VECTOR_SIZE);
    soap_init(&soap);

    if(strcmp(argv[2], "max") == 0){
        soap_call_ordenRemoto_ns__calculateMAX(&soap, argv[1], NULL, mi_vector, &result);
        printf("El maximo es %d.", result);
    }
    else if(strcmp(argv[2], "isSorted") == 0){
        soap_call_ordenRemoto_ns__calculateSorted(&soap, argv[1], NULL, mi_vector, &result);
        if(result == SORTED){
            printf("El vector esta ordenado. \n");
        }
        else{
            printf("El vector no esta ordenado.\n");
        }
    }
    else if(strcmp(argv[2], "sort") == 0){
        soap_call_ordenRemoto_ns__sort(&soap, argv[1], NULL, mi_vector, &vector);
        printf("Vector ordenado: ");
        showVector(vector.__ptr, vector.__size);
    }
    else{
        printf("Operacion introducida incorrecta. \n");
    }

    free(mi_vector.__ptr);
    soap_end(&soap);
    soap_done(&soap);
    return 0;
}