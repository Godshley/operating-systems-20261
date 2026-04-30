#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ticket/ticket.h"
#include "utils/utils.h"

long generar_radicado() {

    srand((unsigned int) time(NULL));

    long radicado = (long) time(NULL) + rand();

    return radicado;
}

Ticket* crear_ticket() {

    Ticket *ticket = (Ticket*) malloc(sizeof(Ticket));

    if(ticket == NULL) {
        printf("Error: no se pudo asignar memoria para el ticket\n");
        return NULL;
    }

    char *entrada = NULL;

    printf("Ingrese identificacion: ");
    entrada = leer_input();

    if(!es_numero(entrada)) {
        printf("Error: la identificacion debe ser numerica\n");
        free(ticket);
        free(entrada);
        return NULL;
    }

    ticket->identificacion = atoi(entrada);

    free(entrada);

    printf("Ingrese correo: ");
    entrada = leer_input();

    if(!validar_correo(entrada)) {
        printf("Error: correo invalido\n");
        free(ticket);
        free(entrada);
        return NULL;
    }

    ticket->correo = entrada;

    printf("Ingrese tipo de reclamacion: ");
    ticket->tipoReclamacion = leer_input();

    if(ticket->tipoReclamacion == NULL) {
        printf("Error leyendo tipo de reclamacion\n");
        free(ticket->correo);
        free(ticket);
        return NULL;
    }

    ticket->radicado = generar_radicado();

    return ticket;
}

int guardar_ticket(Ticket *ticket) {

    if(ticket == NULL)
        return 0;

    char nombre_archivo[100];

    sprintf(nombre_archivo, "assets/ticket_%ld.txt", ticket->radicado);

    FILE *archivo = fopen(nombre_archivo, "w");

    if(archivo == NULL) {
        printf("Error: no se pudo crear el archivo\n");
        return 0;
    }

    fprintf(archivo, "Radicado: %ld\n", ticket->radicado);
    fprintf(archivo, "Identificacion: %d\n", ticket->identificacion);
    fprintf(archivo, "Correo: %s\n", ticket->correo);
    fprintf(archivo, "Tipo de reclamacion: %s\n", ticket->tipoReclamacion);

    fclose(archivo);

    return 1;
}

void liberar_ticket(Ticket *ticket) {

    if(ticket == NULL)
        return;

    free(ticket->correo);
    free(ticket->tipoReclamacion);
    free(ticket);
}
