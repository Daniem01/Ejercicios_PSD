#include <stdio.h>
#include "soapH.h"
#include "ordenRemoto.nsmap"

void bubbleSort(unsigned int array[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                // Intercambio de valores (Swap)
                unsigned int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int ordenRemoto_ns__calculateMAX(struct soap *soap, ordenRemoto_ns__tVector vector, int *resul){
    int max = 0;

    for(int i = 0; i < vector.__size; i++){
        if(vector.__ptr[i] > max){
            max = vector.__ptr[i];
        }
    }

    *resul = max;
    return SOAP_OK;
}

int ordenRemoto_ns__calculateSorted(struct soap *soap, ordenRemoto_ns__tVector vector, int *resul){
    int i = 0, sort = 1;

    while(i < vector.__size - 1 && sort == 1){
        if(vector.__ptr[i] > vector.__ptr[i + 1]){
            sort = 0;
        }
        i++;
    }

    if(sort == 1){
        *resul = SORTED;
    }
    else{
        *resul = NOT_SORTED;
    }

    return SOAP_OK;
}

int ordenRemoto_ns__sort(struct soap *soap, ordenRemoto_ns__tVector vectorEntrada, ordenRemoto_ns__tVector *vectorSalida) {
    
    // Asignamos el tamaño al vector de salida 
    vectorSalida->__size = vectorEntrada.__size;

    // Reservamos memoria dinámica controlada por gSOAP para el array de salida
    vectorSalida->__ptr = (unsigned int *) soap_malloc(soap, vectorEntrada.__size * sizeof(unsigned int));

    // Copiamos los datos originales en nuestro nuevo array
    memcpy(vectorSalida->__ptr, vectorEntrada.__ptr, vectorEntrada.__size * sizeof(unsigned int));

    // Ordenamos el array copiado usando la función auxiliar proporcionada
    bubbleSort(vectorSalida->__ptr, vectorSalida->__size);

    return SOAP_OK;
}

int main(int argc, char **argv){ 
 
  int primarySocket, secondarySocket; 
  struct soap soap; 
 
    if (argc != 2) { 
        printf("Usage: %s <port>\n",argv[0]); 
        exit(-1); 
    } 
 
    // Init environment 
    soap_init(&soap); 
 
    // Bind to the specified port 
    primarySocket = soap_bind(&soap, NULL, atoi(argv[1]), 100); 
 
    // Check result of binding 
    if (primarySocket < 0) { 
        soap_print_fault(&soap, stderr); 
        exit(-1); 
    } 
 
    // Listen to next connection 
    while (1) { 
 
        // accept 
        secondarySocket = soap_accept(&soap); 
 
        if (secondarySocket < 0) { 
        soap_print_fault(&soap, stderr); exit(-1); 
    } 
 
    // Execute invoked operation 
        soap_serve(&soap); 
 
    // Clean up! 
        soap_end(&soap); 
    } 
 
    return 0; 
} 