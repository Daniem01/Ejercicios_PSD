# Variables
CC = mpicc
CFLAGS = -Wall -Wextra -O2 -std=c11
TARGET = progMPI
SRC = divisibles.c

# Número de procesos por defecto para la ejecución
NUM_PROC = 4

# Regla por defecto: compilar el programa
all: $(TARGET)

# Regla para compilar el ejecutable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Regla para ejecutar el programa con MPI
run: $(TARGET)
	mpiexec -np $(NUM_PROC) ./$(TARGET)

# Regla para limpiar los archivos generados
clean:
	rm -f $(TARGET)

# Regla para volver a compilar desde cero
rebuild: clean all

.PHONY: all run clean rebuild