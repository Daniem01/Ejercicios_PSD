#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/** Amount of numbers to be processed */
#define MAX_NUMBERS 15
/** Array size to allocate the results */
#define RESULTS_SIZE 9
/** Workload to be processed by each worker */
#define GRAIN 4
/** Master process */
#define MASTER 0
/** End-of-processing flag */
#define END_OF_PROCESSING -1

// Funtion prototypes
void createNumbers (int* vector, int maxNum);
void executeMaster (int *array, int numProc);
void executeWorker ();

int main(int argc, char *argv[]){
    int numProc, rank;
    int *array;
    // Init MPI
    MPI_Init (&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);
    // Check
    if (numProc < 3){
        printf ("Wrong number of parameters\n");
        MPI_Abort (MPI_COMM_WORLD, 0);
    }
    // Check the number of arguments
    if (argc != 1){
        printf ("Wrong number of parameters\n");
        MPI_Abort (MPI_COMM_WORLD, 0);
    }
    if (GRAIN*(numProc-1) > MAX_NUMBERS){
        printf ("Wrong number\n");
        MPI_Abort (MPI_COMM_WORLD, 0);
    }
    // Master process
    if (rank == MASTER){
        // Allocate memory and create random numbers
        array = (int*) malloc (MAX_NUMBERS * sizeof(int));
        createNumbers (array, MAX_NUMBERS);
        // Execute Master!
        executeMaster (array, numProc);
    }
    // Worker process
    else{
        executeWorker ();
    }
    // End MPI nvironment
    MPI_Finalize();
    return 0;
}

void createNumbers(int* vector, int maxNum) {
    // Rellenamos el array con números aleatorios entre 0 y 99
    for (int i = 0; i < maxNum; i++) {
        vector[i] = rand() % 100;
    }

    printf("Array: ");
    for (int i = 0; i < maxNum; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");
}

void executeMaster (int *array, int numProc){
    MPI_Status status;
    int elem_send = 0;
    int active_workers = numProc - 1;
    int result[RESULTS_SIZE];
    for(int i = 0; i < RESULTS_SIZE; i++){
        result[i] = 0;
    }
    int parcialResult[RESULTS_SIZE];

    // Envio inicial de datos
    for(int j = 1; j < numProc; j++){
        MPI_Send(&array[elem_send], GRAIN, MPI_INT, j, 0, MPI_COMM_WORLD);
        elem_send += GRAIN;
    }

    // Bucle dinamico
    while(active_workers > 0){
        MPI_Recv(parcialResult, RESULTS_SIZE, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        int worker = status.MPI_SOURCE;
        //Guardamos el resultado
        for(int i = 0; i < RESULTS_SIZE; i++){
            result[i] += parcialResult[i];
        }
        // Vemos si hemos acabado o si tenemos mas que mandar
        if(elem_send < MAX_NUMBERS){
            int cuantos_mando = MAX_NUMBERS - elem_send;
            if (cuantos_mando > GRAIN) {
                cuantos_mando = GRAIN; // Si quedan muchos mandamos el grano completo
            }
            // Enviamos el nuevo trozo a ese mismo worker
            MPI_Send(&array[elem_send], cuantos_mando, MPI_INT, worker, 0, MPI_COMM_WORLD);
            elem_send += cuantos_mando;
        }
        else{
            int fin[GRAIN];
            fin[0] = END_OF_PROCESSING;
            MPI_Send(fin, GRAIN, MPI_INT, worker, 0, MPI_COMM_WORLD);
            active_workers--;
        }
    }

    // Imprimir los resultados finales
    printf("Results: ");
    for(int i = 0; i < RESULTS_SIZE; i++){
        printf("%d ", result[i]);
    }
    printf("\n");
}

void executeWorker(){
    MPI_Status status;
    int count;
    int procesar[GRAIN];
    int result[RESULTS_SIZE];
    for(int i = 0; i < RESULTS_SIZE; i++){
        result[i] = 0;
    }

    while(1){
        for(int i = 0; i < RESULTS_SIZE; i++){
            result[i] = 0;
        }

        // Recibimos el paquete
        MPI_Recv(procesar, GRAIN, MPI_INT, MASTER, 0, MPI_COMM_WORLD, &status);
        // Vemos si hay que salir
        if(procesar[0] == END_OF_PROCESSING){
            break;
        }
        else{
            MPI_Get_count(&status, MPI_INT, &count);
            for (int i = 0; i < count; i++) {
                // El bucle interno prueba los divisores del intervalo [1, 9]
                for (int divisor = 1; divisor <= 9; divisor++) {
                    if (procesar[i] % divisor == 0) {
                        // Guardamos el recuento en la posición correspondiente (divisor - 1)
                        result[divisor - 1]++;
                    }
                }
            }
            // Mandamos el resultado
            MPI_Send(result, RESULTS_SIZE, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
        }
    }
}