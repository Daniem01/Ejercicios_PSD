# Variables de compilación
CC = gcc
CFLAGS = -Wall -g
GSOAP_FLAGS = -c

# Herramienta gSOAP
SOAPCPP2 = soapcpp2

# Ejecutables finales
SERVER = server
CLIENT = client

# Regla por defecto: compila todo
all: gsoap $(SERVER) $(CLIENT)

# Paso 1: Generar los stubs y skeletons a partir del .h
gsoap: ordenRemoto.h
	$(SOAPCPP2) $(GSOAP_FLAGS) ordenRemoto.h

# Paso 2: Compilar el Servidor
$(SERVER): server.c soapServer.c soapC.c stdsoap2.c
	$(CC) $(CFLAGS) server.c soapServer.c soapC.c stdsoap2.c -o $(SERVER)

# Paso 3: Compilar el Cliente
$(CLIENT): client.c soapClient.c soapC.c stdsoap2.c
	$(CC) $(CFLAGS) client.c soapClient.c soapC.c stdsoap2.c -o $(CLIENT)

# Regla de limpieza total: borra ejecutables, objetos y TODO lo generado por gSOAP
clean:
	rm -f $(SERVER) $(CLIENT) *.o
	rm -f soapC.c soapH.h soapStub.h soapClient.c soapServer.c soapClientLib.c soapServerLib.c
	rm -f *.nsmap *.wsdl *.xsd
	rm -f *.req.xml *.res.xml ordenRemoto_ns.xml

.PHONY: all gsoap clean