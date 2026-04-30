#ifndef TICKET_H
#define TICKET_H

typedef struct {
    long radicado;
    int identificacion;
    char *correo;
    char *tipoReclamacion;
} Ticket;

Ticket* crear_ticket();
void liberar_ticket(Ticket *ticket);
long generar_radicado();
int guardar_ticket(Ticket *ticket);

#endif
