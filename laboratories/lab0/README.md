# Laboratorio 0 - Sistemas Operativos

## Estudiante
Bryan Giraldo Quintero
CC: 1152457551


---

# Objetivo

Desarrollar habilidades básicas en el uso de la terminal de Linux, manejo de archivos y directorios, redirección de salida y comandos básicos de Git.

---

# Desarrollo del Laboratorio

## Paso 1: Creación del directorio

Se creó la siguiente ruta utilizando el comando:

mkdir -p ~/operating-systems-20261/laboratories/lab0

El parámetro `-p` permitió crear toda la estructura de directorios aunque no existiera previamente.

---

## Paso 2: Navegación al directorio

cd ~/operating-systems-20261/laboratories/lab0

Se verificó la ubicación con:

pwd

---

## Paso 3: Guardar la ruta absoluta

pwd > path.txt

Se redirigió la salida del comando `pwd` al archivo `path.txt`.

---

## Paso 4: Creación de directorios

mkdir example music photos projects

---

## Paso 5: Creación de 100 archivos por directorio

touch example/file{1..100} music/file{1..100} photos/file{1..100} projects/file{1..100}

Se utilizó expansión de llaves para generar automáticamente los archivos.

---

## Paso 6: Eliminación de archivos

rm example/file{1..10} example/file{81..100}
rm music/file{1..10} music/file{81..100}
rm photos/file{1..10} photos/file{81..100}
rm projects/file{1..10} projects/file{81..100}

Quedaron 70 archivos en cada directorio.

---

## Paso 7: Movimiento de directorios

mv example music photos projects/

Se movieron los tres directorios dentro de `projects`.

---

## Paso 8: Eliminación de archivos en modo verboso

rm -v projects/file* > output.txt

Se eliminaron los archivos del directorio `projects` y se redirigió la salida al archivo `output.txt`.

---

# Atajos utilizados en la terminal

- TAB → autocompletar comandos
- Flecha arriba ↓ → historial de comandos
- Ctrl + L → limpiar pantalla
- Ctrl + O → guardar en nano
- Ctrl + X → salir de nano

---

# Estructura final del laboratorio

operating-systems-20261/
└── laboratories/
    └── lab0/
        ├── path.txt
        ├── output.txt
        ├── README.md
        ├── projects/
            ├── example/
            ├── music/
            └── photos/
