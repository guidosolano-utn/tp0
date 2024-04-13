#include "client.h"


int main(void)
{
	
	char* ip;
	char* puerto;
	char* valor ;
	char* file_1 = "tp0.log";
	int  *conexion;

	
	char *path = "cliente.config";
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
	
	log_info(logger, "1)Hola! Soy un log\n");


	config=config_create(path);


	if ( config == NULL) {
    	printf("2)¡No se pudo crear el config!\n");
		return 1;
	}
	else printf("2)¡Pude crear la config!\n");


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
	
	*conexion = crear_conexion(ip,puerto);

	enviar_mensaje (valor,conexion);

	paquete(conexion);

	terminar_programa( conexion, logger,  config);

	return 0;
}


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
	int tamanio_leido;

	leido = readline("> ");

	log_info(logger,"%s",leido);

	free(leido);
}

void paquete(int conexion)
{
	char* leido;
	t_paquete* paquete;

	paquete = crear_paquete();	

	agregar_a_paquete(paquete,conexion, conexion );

	enviar_paquete(paquete,conexion);	
	 
	eliminar_paquete(paquete);	
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	liberar_conexion (conexion);

	config_destroy(config);
	
	log_destroy(logger); 

	printf ("Termine el programa\n");
}
