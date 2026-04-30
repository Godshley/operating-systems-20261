#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils/utils.h"

void limpiar_salto_linea(char *str) {

    if(str == NULL)
        return;

    str[strcspn(str, "\n")] = '\0';
}

int es_numero(const char *str) {

    if(str == NULL || *str == '\0')
        return 0;

    for(int i = 0; str[i] != '\0'; i++) {

        if(!isdigit(str[i]))
            return 0;
    }

    return 1;
}

int validar_correo(const char *correo) {

    if(correo == NULL || *correo == '\0')
        return 0;

    if(strchr(correo, '@') == NULL)
        return 0;

    return 1;
}

char* leer_input() {

    char buffer[256];

    if(fgets(buffer, sizeof(buffer), stdin) == NULL)
        return NULL;

    limpiar_salto_linea(buffer);

    char *input = (char*) malloc(strlen(buffer) + 1);

    if(input == NULL) {
        printf("Error: no se pudo asignar memoria\n");
        return NULL;
    }

    strcpy(input, buffer);

    return input;
}
