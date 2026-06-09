# =========================================================================
# Makefile para el Proyecto de Multiplicación de Matrices Dinámica con MPI
# Asignatura: Programación de Sistemas Distribuidos
# =========================================================================

# Compilador y Ejecutor de MPI
CC      = mpicc
MPIRUN  = mpirun

# Flags de compilación: 
# -Wall: Muestra todas las advertencias (warnings) para un código limpio
# -O2: Aplica optimizaciones de nivel 2 para mejorar el rendimiento matemático
CFLAGS  = -Wall -O2
LIBS    = 

# Nombre del archivo ejecutable de salida
TARGET  = matrices_mpi

# Archivos fuente y objetos (Cambia 'matrices.c' si tu archivo se llama diferente)
SRC     = matrices.c
OBJ     = $(SRC:.c=.o)

# Número de procesos por defecto para mpirun (1 Master + 3 Workers)
NP      = 4

.PHONY: all clean run help

# Regla por defecto: Compila el proyecto
all: $(TARGET)

# Vinculación del ejecutable
$(TARGET): $(OBJ)
	@echo "[LINK] Enlazando objetos para generar el ejecutable: $@"
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBS)
	@echo "[SUCCESS] Compilación completada con éxito."

# Compilación de archivos de código fuente (.c) a objetos (.o)
%.o: %.c
	@echo "[CC] Compilando archivo fuente: $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar los archivos binarios y temporales generados
clean:
	@echo "[CLEAN] Eliminando archivos objeto y ejecutables..."
	rm -f $(OBJ) $(TARGET)
	@echo "[CLEAN] Limpieza completada."

# Regla para ejecutar el programa en paralelo con mpirun
run: $(TARGET)
	@echo "[RUN] Ejecutando el programa con $(NP) procesos en paralelo..."
	@echo "------------------------------------------------------------------"
	$(MPIRUN) -np $(NP) ./$(TARGET)
	@echo "------------------------------------------------------------------"

# Ayuda del Makefile para recordar los comandos disponibles
help:
	@echo "Opciones disponibles en este Makefile:"
	@echo "  make          - Compila el proyecto y genera el ejecutable '$(TARGET)'"
	@echo "  make clean    - Borra los archivos objeto (.o) y el ejecutable"
	@echo "  make run      - Ejecuta el programa con $(NP) procesos (por defecto)"
	@echo "  make run NP=6 - Ejecuta el programa con un número específico de procesos (ej: 6)"
	@echo "  make help     - Muestra este menú de ayuda"