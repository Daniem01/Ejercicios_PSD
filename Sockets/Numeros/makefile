# Opciones de compilación
CC = gcc
CFLAGS = -Wall -Wextra -g
LIBS = -pthread

# Nombres de los ejecutables finales
CLIENT = client
SERVER = server

# Archivos fuente y cabeceras
DEPS = types.h

# Regla por defecto: compila ambos ejecutables
all: $(CLIENT) $(SERVER)

# Regla para compilar el cliente
$(CLIENT): client.c $(DEPS)
	$(CC) $(CFLAGS) client.c -o $(CLIENT) $(LIBS)

# Regla para compilar el servidor
$(SERVER): server.c $(DEPS)
	$(CC) $(CFLAGS) server.c -o $(SERVER) $(LIBS)

# Limpieza de ejecutables y archivos temporales
clean:
	rm -f $(CLIENT) $(SERVER)

.PHONY: all clean