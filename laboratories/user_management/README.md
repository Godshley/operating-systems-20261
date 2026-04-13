# Sistema de Administración de Usuarios en Linux (Bash + Podman)

## Descripción del proyecto

Este proyecto implementa un sistema de administración de usuarios en Linux utilizando Bash scripting dentro de un contenedor gestionado con Podman.

El sistema permite gestionar usuarios del sistema operativo aplicando políticas de seguridad reales como expiración de contraseñas, validación de credenciales, control de acceso mediante sudo restringido y auditoría de acciones mediante logs.

El desarrollo sigue un enfoque modular inspirado en los principios SOLID, facilitando mantenimiento, escalabilidad y claridad en el código.

---

## Funcionalidades del sistema

* Listar usuarios locales
* Crear usuarios con contraseña por defecto
* Bloquear usuarios
* Activar (desbloquear) usuarios
* Eliminar usuarios
* Agregar usuarios a un grupo de sudoers restringido al laboratorio
* Forzar cambio de contraseña en el primer ingreso
* Validación de contraseñas seguras:

  * Sin espacios
  * Al menos una mayúscula
  * Al menos un carácter especial
* Aviso de vencimiento de contraseña 10 días antes
* Bloqueo automático de cuentas con contraseña vencida
* Registro de acciones en logs

---

## Estructura del proyecto

```
user_management/
├── main.sh
├── modules/
│   ├── user_create.sh
│   ├── user_list.sh
│   ├── user_delete.sh
│   ├── user_lock.sh
│   ├── user_unlock.sh
│   └── user_passwd.sh
│
├── utils/
│   ├── password_validator.sh
│   └── logger.sh
│
└── logs/
    └── actions.log
```

---

## Ejecución en Podman

```bash
podman pull alpine
podman run -it --name lab_usuarios alpine sh

apk update
apk add shadow sudo bash
```

Luego copiar el proyecto a `/app`.

---

## Guía de uso

Ejecutar el sistema:

```bash
sudo /app/main.sh
```

Opciones disponibles:

1. Crear usuario
2. Listar usuarios
3. Bloquear usuario
4. Desbloquear usuario
5. Eliminar usuario
6. Cambiar contraseña
7. Salir

---

## Políticas de seguridad

* Contraseña por defecto: `Temp123*`
* Cambio obligatorio en primer login
* Expiración de contraseña a 30 días
* Advertencia 10 días antes del vencimiento
* Bloqueo automático al expirar
* Validación de contraseña robusta
* Sudo restringido al comando `/app/main.sh`
* Registro de acciones en logs

---

## Consideraciones técnicas

* Sistema ejecutado en contenedor Podman con Alpine Linux
* Uso de herramientas del sistema (`useradd`, `chage`, `passwd`)

---
