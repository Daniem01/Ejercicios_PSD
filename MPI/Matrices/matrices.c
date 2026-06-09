#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SIZE 1000
#define MAX_INT_NUMBER 10
#define MASTER 0
#define END_OF_PROCESSING -1

// Definimos tMatrix como un array aplanado de tamaño SIZE * SIZE
typedef int tMatrix[SIZE * SIZE];

// Prototipos de las funciones
void generateMatrix(tMatrix matrix);
void executeMaster(tMatrix *matrixA, tMatrix *matrixB, tMatrix *matrixC, int numProc);
void executeWorker(int myrank);


void generateMatrix(tMatrix matrix){
    int i;
    for (i=0; i<(SIZE*SIZE); i++)
        matrix[i] = (rand() % MAX_INT_NUMBER);
}

/**
 * Multiplica una fila de la Matriz A por una columna concreta de la Matriz B aplanada.
 * Devuelve el resultado entero (el producto escalar).
 */
int multiplicarFilaPorColumna(int *fila_A, int *matrixB, int columna_B) {
    int resultado = 0;

    // Recorremos los SIZE elementos de la fila de A y de la columna de B
    for (int k = 0; k < SIZE; k++) {
        // k recorre de izquierda a derecha la fila_A
        // (k * SIZE + columna_B) recorre de arriba a abajo la columna de matrixB
        resultado += fila_A[k] * matrixB[(k * SIZE) + columna_B];
    }

    return resultado;
}

int main(int argc, char *argv[]){
    int numProc;
    int myrank;

    // Init MPI
    MPI_Init (&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);

    if (numProc < 3){
        printf ("Wrong number of parameters\n");
        MPI_Abort (MPI_COMM_WORLD, 0);
    }
    // Check the number of arguments
    if (argc != 1){
        printf ("Wrong number of parameters\n");
        MPI_Abort (MPI_COMM_WORLD, 0);
    }
    // Master
    if (myrank == MASTER) {
        // Reservamos memoria dinámica para las matrices del Master
        tMatrix *matrixA = (tMatrix*) malloc(sizeof(tMatrix));
        tMatrix *matrixB = (tMatrix*) malloc(sizeof(tMatrix));
        tMatrix *matrixC = (tMatrix*) malloc(sizeof(tMatrix));

        // Rellenamos las matrices A y B con números aleatorios
        generateMatrix(*matrixA);
        generateMatrix(*matrixB);

        executeMaster(matrixA, matrixB, matrixC, numProc); 

        free(matrixA);
        free(matrixB);
        free(matrixC);
    } 
    // Worker
    else {
        executeWorker(myrank);
    }

    MPI_Finalize();
    return 0;
}

void executeMaster(tMatrix *matrixA, tMatrix *matrixB, tMatrix *matrixC, int numProc){
    MPI_Status status;
    int filas_mandadas = 0;
    int fila_recibida[SIZE];
    int active_workers = numProc - 1;

    // Mandamos a todos los workers la matriz B entera
    MPI_Bcast(matrixB, SIZE * SIZE, MPI_INT, MASTER, MPI_COMM_WORLD);

    // Primer envío de cada fila (usamos filas_mandadas como TAG)
    for(int i = 1; i < numProc; i++){
        MPI_Send(&((*matrixA)[filas_mandadas * SIZE]), SIZE, MPI_INT, i, filas_mandadas, MPI_COMM_WORLD);
        filas_mandadas++;
    }

    // Bucle dinámico bajo demanda
    while(active_workers > 0){
        // IMPORTANTE: Escuchamos cualquier TAG para saber qué fila nos llega
        MPI_Recv(fila_recibida, SIZE, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        
        int worker = status.MPI_SOURCE;
        int id_fila = status.MPI_TAG; // El número real de la fila calculada

        // Guardamos la fila recibida en su posición matemática exacta
        for(int j = 0; j < SIZE; j++){
            (*matrixC)[(id_fila * SIZE) + j] = fila_recibida[j];
        }

        // Si quedan filas por mandar, le pasamos otra al worker que se ha liberado
        if(filas_mandadas < SIZE){
            // Enviamos la fila pasándole su índice real en el TAG
            MPI_Send(&((*matrixA)[filas_mandadas * SIZE]), SIZE, MPI_INT, worker, filas_mandadas, MPI_COMM_WORLD);
            filas_mandadas++;
        }
        // Si no quedan filas, le mandamos la señal de cierre
        else{
            int fila_fin[SIZE];
            fila_fin[0] = END_OF_PROCESSING;
            MPI_Send(fila_fin, SIZE, MPI_INT, worker, 0, MPI_COMM_WORLD);
            active_workers--;
        }
    }
}

void executeWorker(int myrank){
    MPI_Status status;
    tMatrix matrixB;
    int fila_A[SIZE];
    int fila_C[SIZE];

    // Recibimos la matriz B
    MPI_Bcast(matrixB, SIZE * SIZE, MPI_INT, MASTER, MPI_COMM_WORLD);

    // Bucle de trabajo
    while(1){
        MPI_Recv(fila_A, SIZE, MPI_INT, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        int fila_ID = status.MPI_TAG;
        // Vemos si hemos acabado
        if(fila_A[0] == END_OF_PROCESSING){
            break;
        }
        else{
            // Copiamos
            for (int col = 0; col < SIZE; col++) {
                fila_C[col] = multiplicarFilaPorColumna(fila_A, matrixB, col);
            }
            // Mandamos
            MPI_Send(fila_C, SIZE, MPI_INT, MASTER, fila_ID, MPI_COMM_WORLD);
            printf("Worker %d: He terminado de calcular la fila %d\n", myrank, fila_ID);
        }
    }
}