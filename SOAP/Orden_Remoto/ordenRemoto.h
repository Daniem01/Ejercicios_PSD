//gsoap ordenRemoto_ns service name: ordenRemoto 
//gsoap ordenRemoto_ns service style: rpc 
//gsoap ordenRemoto_ns service encoding: encoded 
//gsoap ordenRemoto_ns service namespace: urn: ordenRemoto 
 
/** Maximum length for the vector */ 
#define MAX_VECTOR_SIZE 10 
 
/** Maximum value for the numbers */ 
#define MAX_VALUE 10000 
 
/** Result for a sorted vector */ 
#define SORTED 1 
 
/** Result for a not sorted vector */ 
#define NOT_SORTED 0 
 
/** Struct that contains a vector */ 
typedef struct tVector{ 
    int __size; 
    unsigned int *__ptr; 
}ordenRemoto_ns__tVector;

int ordenRemoto_ns__calculateMAX(ordenRemoto_ns__tVector vector, int *resul);
int ordenRemoto_ns__calculateSorted(ordenRemoto_ns__tVector vector, int *resul);
int ordenRemoto_ns__sort(ordenRemoto_ns__tVector vectorEntrada, ordenRemoto_ns__tVector *vectorSalida);