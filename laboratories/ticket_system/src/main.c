#include <stdio.h>
#include <stdlib.h>
#include "ticket/ticket.h"

int main() {

    printf("=================================\n");
    printf("  SISTEMA DE TICKETS DE SOPORTE\n");
    printf("=================================\n\n");

    Ticket *ticket = crear_ticket();

    if(ticket == NULL) {
        printf("No se pudo crear el ticket\n");
        return 1;
    }

    if(!guardar_ticket(ticket)) {
        printf("Error guardando el ticket\n");
        liberar_ticket(ticket);
        return 1;
    }

    printf("\nTicket registrado correctamente\n");
    printf("Numero de radicado: %ld\n", ticket->radicado);

    liberar_ticket(ticket);

    return 0;
}
