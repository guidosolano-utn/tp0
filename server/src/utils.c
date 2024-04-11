#include"utils.h"

t_log* logger;

int iniciar_servidor(void)
{
	
	printf("Iniciando Servidor...\n");

	int socket_servidor;
	int err;

	struct addrinfo hints, *servinfo, *p;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, PUERTO, &hints, &servinfo);

	err = getaddrinfo(NULL, "4444", &hints, &servinfo);

	if (err == -1 ) {printf("Error\n"); exit (-1);}
	else printf("Entregando Datos del Socket...\n");

	// Creamos el socket de escucha del servidor
	int fd_escucha = socket(servinfo->ai_family,
                       		servinfo->ai_socktype,
                        	servinfo->ai_protocol);

	// Asociamos el socket a un puerto

	err = bind(fd_escucha, servinfo->ai_addr, servinfo->ai_addrlen);
	if (err == -1 ) {printf("Error\n"); exit (-1);}
	else printf("Uniendo Socket al Puerto...\n");

	err = listen(fd_escucha, SOMAXCONN);	
	if (err == -1 ) {printf("Error\n"); exit (-1);}
	else printf("Esperando al Cliente en el Socket...\n");

	// Escuchamos las conexiones entrantes

	int fd_conexion = accept(fd_escucha, NULL, NULL);
	if (err == -1 ) {printf("Error\n"); exit (-1);}
	else printf("Aceptando Conexion...\n");


	freeaddrinfo(servinfo);
	log_trace(logger, "Listo para escuchar a mi cliente");

	return socket_servidor;
}

int esperar_cliente(int socket_servidor)
{
	// Quitar esta línea cuando hayamos terminado de implementar la funcion
	assert(!"no implementado!");

	// Aceptamos un nuevo cliente
	int socket_cliente;
	log_info(logger, "Se conecto un cliente!");

	return socket_cliente;
}

int recibir_operacion(int socket_cliente)
{
	int cod_op;
	if(recv(socket_cliente, &cod_op, sizeof(int), MSG_WAITALL) > 0)
		return cod_op;
	else
	{
		close(socket_cliente);
		return -1;
	}
}

void* recibir_buffer(int* size, int socket_cliente)
{
	void * buffer;

	recv(socket_cliente, size, sizeof(int), MSG_WAITALL);
	buffer = malloc(*size);
	recv(socket_cliente, buffer, *size, MSG_WAITALL);

	return buffer;
}

void recibir_mensaje(int socket_cliente)
{
	int size;
	char* buffer = recibir_buffer(&size, socket_cliente);
	log_info(logger, "Me llego el mensaje %s", buffer);
	free(buffer);
}

t_list* recibir_paquete(int socket_cliente)
{
	int size;
	int desplazamiento = 0;
	void * buffer;
	t_list* valores = list_create();
	int tamanio;

	buffer = recibir_buffer(&size, socket_cliente);
	while(desplazamiento < size)
	{
		memcpy(&tamanio, buffer + desplazamiento, sizeof(int));
		desplazamiento+=sizeof(int);
		char* valor = malloc(tamanio);
		memcpy(valor, buffer+desplazamiento, tamanio);
		desplazamiento+=tamanio;
		list_add(valores, valor);
	}
	free(buffer);
	return valores;
}
