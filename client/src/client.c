#include "client.h"


int main(void)
{
	
	char* ip;
	char* puerto;
	char* valor ;
	char* file_1 = "tp0.log";
	char* conexion;

	
	char *path = "/home/utnso/cliente.config";
	char* key = "IP";
	char *puerto_key= "PUERTO";
	char *valor_key= "CLAVE";

	t_log* logger;
	t_config* config;


	
	/* ---------------- LOGGING ---------------- */

	logger = log_create(file_1,"tp0.logger",true, LOG_LEVEL_INFO); // Aca creo el logger

    if (logger == NULL) {
        printf("¡No se pudo crear el logger!\n");
        return 1; 
    }
	
	log_info(logger, "\n1)Hola! Soy un log\n");


	config=config_create(path);


	if ( config == NULL) {
    	printf("2)¡No se pudo crear el config!\n");
		return 1;
	}
	else printf("2)¡Pude crear la config!\n");

	/*config_bool = config_has_property(config, key);
	
	if ( config_bool != true ) {
		 printf("¡No se pudo encontrar la clave en el archivo de configuración!\n");
		return 1;
	}
	else printf("¡Pude crear el bool\n");*/

	ip = config_get_string_value(config, key);
	
	if (ip == NULL) {
		 printf("3)¡No se pudo obtener el valor del ip en el archivo de configuración!\n");
		return 1;
	}
	else printf("3)Obtuve la ip \n"); 

	valor = config_get_string_value(config, valor_key);
	
	if (valor == NULL) {
		 printf("4)¡No se pudo obtener el valor del valor en el archivo de configuración!\n");
		return 1;
	}
	else printf("4)Obtuve el valor\n");


	puerto = config_get_string_value(config, puerto_key);
	
	if (puerto == NULL) {
		 printf("5)¡No se pudo obtener el valor del puerto clave en el archivo de configuración!\n");
		return 1;
	}
	else printf("5)Obtuve el puerto\n");

	printf("\n----------LOGG INFO----------------\n\n");

	log_info(logger,"IP: %s",ip);
	log_info(logger,"PUERTO: %s",puerto);
	log_info(logger,"CLAVE: %s",valor);
	

	leer_consola(logger); //Leemos y escribimos en el logg
	
	printf("\n----------CONEXION A SERVIDOR----------------\n\n");
	
	t_paquete * paquete;

	conexion = crear_conexion(ip,puerto);

	paquete = crear_paquete();						//Nos crea el paquete que vamos a mandar.

	printf("6)Cree el Paquete\n");

	agregar_a_paquete(paquete,valor, (strlen(valor)+1) );	//Dado un stream y su tamaño, lo agrega al paquete.

	printf("7)Cargue el Paquete\n");

	enviar_mensaje (valor,conexion);

	enviar_paquete(paquete,conexion);				//Dada una conexión y un paquete, lo envía a través de ella.

	printf("8)Envie el Paquete\n");

	eliminar_paquete(paquete);						//Elimina la memoria usada por el paquete.

	printf("9)Destrui el Paquete\n");

	liberar_conexion (conexion);

	config_destroy(config);
	
	log_destroy(logger); 

    printf("10)Destrui el log!\n");

	return 0;
}

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	//conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje

	// Armamos y enviamos el paquete
	//paquete(conexion);

	//terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío


	// ¡No te olvides de liberar las lineas antes de regresar!

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	// Leemos y esta vez agregamos las lineas al paquete


	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
