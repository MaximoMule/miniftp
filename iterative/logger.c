#include "logger.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Variable estática para rastrear si se inicializó el logger
 */
static int logger_initialized = 0;

void logger_init(const char *program_name) {
    /**
     * openlog configura syslog:
     * - program_name: identificador del programa en los logs
     * - LOG_PID: incluye el PID del proceso en cada mensaje
     * - LOG_ODELAY: abre conexión solo cuando sea necesario (lazy initialization)
     * - LOG_USER: facility (tipo de aplicación)
     */
    openlog(program_name, LOG_PID | LOG_ODELAY, LOG_USER);
    logger_initialized = 1;
}

void logger(int priority, const char *format, ...) {
    va_list args;
    va_start(args, format);

    if (!logger_initialized) {
        /**
         * Si el logger no fue inicializado, usamos vfprintf a stderr como fallback
         * Esto permite usar logger() antes de llamar logger_init()
         */
        vfprintf(stderr, format, args);
        fprintf(stderr, "\n");
        va_end(args);
        return;
    }

    /**
     * Envía el mensaje a syslog con el nivel de severidad especificado
     */
    vsyslog(priority, format, args);
    va_end(args);
}

void logger_close(void) {
    if (logger_initialized) {
        closelog();
        logger_initialized = 0;
    }
}
