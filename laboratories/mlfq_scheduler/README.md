## Descripción

Este proyecto implementa una **simulación del algoritmo de planificación de procesos Multi-Level Feedback Queue (MLFQ)** utilizando el lenguaje **C**.

El objetivo es modelar el comportamiento de un scheduler de sistemas operativos usando **múltiples colas de prioridad** con diferentes quantums de ejecución, mejorando el tiempo de respuesta para procesos interactivos sin sacrificar el rendimiento de los procesos largos.

La simulación incluye:

* Manejo de arrival time
* Tres niveles de prioridad
* Demotion entre colas
* Priority Boost
* Cálculo de métricas de scheduling
* Exportación de resultados a CSV

---

# Algoritmo MLFQ

Este algoritmo organiza los procesos en múltiples colas de prioridad.

Las características principales del algoritmo son:

1. Los procesos nuevos ingresan a la cola de mayor prioridad.
2. Cada cola tiene un quantum diferente.
3. Si un proceso usa todo su quantum, es degradado a una cola de menor prioridad.
4. Periódicamente se ejecuta un priority boost, que devuelve todos los procesos a la cola de mayor prioridad para evitar starvation.

Configuración utilizada en este laboratorio:

| Cola | Quantum |
| ---- | ------- |
| Q0   | 2       |
| Q1   | 4       |
| Q2   | 8       |

Priority Boost: **cada 20 ciclos de CPU**

---

# Escenario de prueba

| PID | Arrival | Burst |
| --- | ------- | ----- |
| P1  | 0       | 8     |
| P2  | 1       | 4     |
| P3  | 2       | 9     |
| P4  | 3       | 5     |

---

# Métricas calculadas

El scheduler calcula las siguientes métricas clásicas de planificación:

### Response Time

Tiempo desde que el proceso llega al sistema hasta que se ejecuta por primera vez.

```
Response Time = Start Time - Arrival Time
```

### Turnaround Time

Tiempo total desde que el proceso llega hasta que finaliza.

```
Turnaround Time = Finish Time - Arrival Time
```

### Waiting Time

Tiempo total que el proceso permanece esperando en las colas.

```
Waiting Time = Turnaround Time - Burst Time
```

Los resultados se exportan automáticamente a:

```
assets/results.csv
```

---

# Estructura del proyecto

```
mlfq_scheduler
│
├── assets
│   └── results.csv
│
├── include
│   ├── metrics
│   │   └── metrics.h
│   ├── process
│   │   └── process.h
│   ├── queue
│   │   └── queue.h
│   └── scheduler
│       └── scheduler.h
│
├── src
│   ├── main.c
│   ├── metrics
│   │   └── metrics.c
│   ├── process
│   │   └── process.c
│   ├── queue
│   │   └── queue.c
│   └── scheduler
│       └── scheduler.c
│
├── Makefile
└── README.md
```

---

# Descripción de los módulos

## Process

Este contiene información como:

* PID
* arrival time
* burst time
* remaining time
* start time
* finish time

Archivo principal:

```
process.h
```

Define la estructura:

```
typedef struct Process
```

y las funciones usadas para la creación de procesos.

---

## Queue

Funciones principales:

* enqueue()
* dequeue()
* is_empty()

---

## Scheduler

Contiene la lógica principal.

En este definimos:

* Las tres colas de prioridad
* Los quantums de cada cola
* El tiempo actual del sistema
* El intervalo de priority boost

Funciones principales:

### create_scheduler()

Inicializa las colas y parámetros del scheduler.

### add_process()

Inserta un proceso en la cola de mayor prioridad.

### get_next_process()

Selecciona el siguiente proceso a ejecutar según la prioridad.

### run_process()

Simula la ejecución del proceso durante su quantum.

### priority_boost()

Mueve todos los procesos nuevamente a la cola de mayor prioridad.

---

## Metrics

Calcula y muestra las métricas solicitadas.

Funciones:

* print_metrics()
* export_metrics_csv()

---

# Flujo de ejecución del programa

El flujo principal se encuentra en:

```
src/main.c
```

Pasos principales:

1. Crear el scheduler
2. Crear los procesos de prueba
3. Simular el paso del tiempo
4. Insertar procesos cuando llega su arrival time
5. Ejecutar el proceso seleccionado
6. Actualizar métricas cuando el proceso finaliza
7. Exportar resultados a CSV

---

# Compilación

```
make
```

---

# Ejecución

```
make run
```

---

# Limpieza del proyecto

```
make clean
```

---

# Resultados

Ejemplo de salida:

```
Running process 1 in Q0
Process 1 demoted to Q1
...
===== SCHEDULER METRICS =====
Metrics for process 1
Response Time: 0
Turnaround Time: 23
Waiting Time: 15
```

---

# Análisis del algoritmo

## ¿Qué ocurre si el boost es muy frecuente?

Si ocurre con mucha frecuencia, todos los procesos regresan constantemente a la cola de mayor prioridad.

Esto hace que el scheduler se comporte de forma similar a Round Robin, ya que los procesos no permanecen tiempo suficiente en colas de menor prioridad.

Si esto ocurre, se reduce la efectividad del algoritmo ya que es dificil diferenciar los procesos interactivos y los largos.

---

## ¿Qué ocurre si no existe boost?

Si no se implementa el boost, los procesos largos que han sido degradados a colas de baja prioridad pueden permanecer allí de forma indefinida.

Esto puede provocar que los procesos largos se queden esperando de forma excesiva o que los procesos agiles monopolicen las colas superiores.

En casos extremos se produce 'starvation'.

---

## ¿Cómo afecta un quantum pequeño en la cola de mayor prioridad?

Un quantum pequeño en este caso, nos ayuda a detectar los procesos que son interactivos o de corta duración.

Esto hace que los procesos interactivos terminen de una manera veloz y mejora el tiempo de respuesta.

---

## ¿Puede haber starvation?

Sí, puede ocurrir si los procesos de baja prioridad no se ejecutan de nuevo debido a la constante llegadae de nuevos procesos en colas superiores.

El mecanismo de boost se implementa precisamente para evitar este problema.
