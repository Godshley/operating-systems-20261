# Sistema de Registro de Tickets de Reclamación

Este proyecto implementa una aplicación de consola en lenguaje C para el registro de tickets de reclamación.  
El sistema permite capturar información del usuario, generar un número de radicado único y almacenar los datos en un archivo.

El objetivo del proyecto es demostrar el uso adecuado de:

- Modularización del código
- Uso de punteros
- Manejo de memoria dinámica
- Manejo de archivos
- Validación de datos
- Uso de Makefile
- Organización de proyectos en C

---

# Características del sistema

El sistema permite:

- Registrar tickets de reclamación desde la consola
- Validar la identificación ingresada
- Validar el formato del correo electrónico
- Generar un número de radicado automáticamente
- Guardar los tickets en un archivo
- Liberar memoria correctamente para evitar memory leaks

---

# Estructura del proyecto

```
ticket_system
│
├── Makefile
├── README.md
│
├── assets
│   └── tickets.txt
│
├── include
│   ├── ticket
│   │   └── ticket.h
│   │
│   └── utils
│       └── utils.h
│
└── src
    ├── main.c
    │
    ├── ticket
    │   └── ticket.c
    │
    └── utils
        └── utils.c
```

---

# Compilación del programa

Para compilar el proyecto se utiliza **Makefile**.

Desde la carpeta raíz ejecutar:

```
make
```

Esto generará el ejecutable:

```
ticket_app
```

---

# Ejecución del programa

Para ejecutar el sistema:

```
make run
```

O directamente:

```
./ticket_app
```

---

# Limpieza del proyecto

Para eliminar el ejecutable generado:

```
make clean
```

---

# Ejemplo de uso

Ejemplo de ejecución del programa:

```
Ingrese identificacion: 123456789
Ingrese correo: usuario@correo.com
Ingrese tipo de reclamacion: Servicio
```

Salida del sistema:

```
Ticket registrado correctamente
Numero de radicado: 1741400023
```

Los datos quedan almacenados en el archivo:

```
assets/tickets.txt
```

---

---

# Explicación técnica del desarrollo

# Uso de punteros

Se han utilizado principalmente en la estructura `Ticket`.

Archivo:

```
include/ticket/ticket.h
```

Definición:

```
typedef struct {
    long radicado;
    int identificacion;
    char *correo;
    char *tipoReclamacion;
} Ticket;
```

Las variables `correo` y `tipoReclamacion` son **punteros a char**, lo que permite almacenar cadenas de tamaño dinámico.

También se uso un puntero para manejar la estructura completa:

```
Ticket *ticket;
```

Esto nos permite crear la estructura dinámicamente usando memoria del heap.

Ejemplo de uso en:

```
src/ticket/ticket.c
```

```
Ticket *ticket = malloc(sizeof(Ticket));
```

---

# Manejo de memoria dinámica

En el proyecto, se hace uso de memoria dinámica para almacenar datos ingresados por el usuario.

Se utiliza la función:

```
malloc()
```

para reservar memoria en tiempo de ejecución.

Ejemplo en:

```
src/utils/utils.c
```

Dentro de la función:

```
char* leer_input()
```

Se reserva memoria para almacenar la entrada del usuario.

Luego se copia la cadena leída y se retorna un puntero a dicha memoria.

Para evitar **memory leaks**, la memoria reservada se libera con:

```
free()
```

Implementado en la función:

```
liberar_ticket()
```

Archivo:

```
src/ticket/ticket.c
```

```
void liberar_ticket(Ticket *ticket) {

    if(ticket == NULL)
        return;

    free(ticket->correo);
    free(ticket->tipoReclamacion);
    free(ticket);
}
```

Esta función libera toda la memoria asociada al ticket una vez que el programa finaliza.

---

# Generación del número de radicado

El número de radicado se genera automáticamente utilizando el tiempo del sistema.

Archivo:

```
src/ticket/ticket.c
```

Función:

```
long generar_radicado()
```

Implementación:

```
long generar_radicado() {
    return time(NULL);
}
```
---

# Manejo de errores

El sistema implementa validaciones para evitar datos incorrectos y errores ingresados por el usuario.

Las validaciones incluyen:

### Validación de número

Archivo:

```
src/utils/utils.c
```

Función:

```
int es_numero(const char *str)
```

Esta función verifica que todos los caracteres ingresados sean dígitos.

---

### Validación de correo

Archivo:

```
src/utils/utils.c
```

Función:

```
int validar_correo(const char *correo)
```

La validación verifica que el correo contenga:

- el carácter `@`
- el carácter `.`

Si el correo no cumple con estos requisitos, se muestra un mensaje de error.

---

### Verificación de memoria

Cada vez que se usa `malloc` se verifica que la memoria se haya reservado correctamente.

Ejemplo:

```
Ticket *ticket = malloc(sizeof(Ticket));

if(ticket == NULL) {
    printf("Error al reservar memoria\n");
    return NULL;
}
```

Esto evita que el programa continúe ejecutándose si falla la asignación de memoria.

---

# Funcionamiento del Makefile

El proyecto utiliza un **Makefile** para automatizar la compilación.

Archivo:

```
Makefile
```

El Makefile define tres comandos principales:

### Compilar el proyecto

```
make
```

Compila todos los archivos fuente:

```
src/main.c
src/utils/utils.c
src/ticket/ticket.c
```
---

### Ejecutar el programa

```
make run
```

Este comando ejecuta el programa compilado:

```
./ticket_app
```

---

### Limpiar archivos compilados

```
make clean
```

Elimina el ejecutable generado para mantener el proyecto limpio.

```bash
rm -f ticket_app
```

Esto permite recompilar el proyecto desde cero cuando sea necesario.

---

# Autor

Proyecto desarrollado por: Bryan Giraldo Quintero
