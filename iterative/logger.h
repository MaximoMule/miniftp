#ifndef LOGGER_H
#define LOGGER_H

#include <syslog.h>
#include <stdarg.h>

/**
 * Inicializa el sistema de logging con syslog
 * Debe llamarse al inicio de main(), antes de crear el servidor
 * 
 * @param program_name Nombre del programa (ej: "ftp-server")
 */
void logger_init(const char *program_name);

/**
 * Función universal que reemplaza printf/fprintf/perror
 * Envía mensajes a syslog del sistema
 * 
 * Uso:
 *   logger(LOG_INFO, "Starting server on %s:%d", ip, port);
 *   logger(LOG_ERR, "Error creating socket");
 *   logger(LOG_DEBUG, "Child PID %d", getpid());
 * 
 * @param priority Nivel de severidad (LOG_DEBUG, LOG_INFO, LOG_ERR, etc)
 * @param format String de formato como printf
 * @param ... Argumentos variables
 */
void logger(int priority, const char *format, ...);

/**
 * Cierra la conexión a syslog al terminar el programa
 * Opcional pero recomendado
 */
void logger_close(void);

#endif
