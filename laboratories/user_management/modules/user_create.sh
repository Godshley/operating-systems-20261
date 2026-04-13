#!/bin/bash

# Cargar el logger
source /app/utils/logger.sh

echo "=== CREAR USUARIO ==="

read -p "Ingrese nombre de usuario: " username

# Validar que no esté vacío
if [ -z "$username" ]; then
    echo "Error: nombre vacío"
    exit 1
fi

# Verificar si ya existe
if id "$username" &>/dev/null; then
    echo "El usuario ya existe"
else
    useradd -m -G labusers "$username"

    # contraseña por defecto
    echo "$username:Abc123*" | chpasswd

    # Forzar cambio contrasena en primer login
chage -d 0 "$username"

    # Expiración de contraseña (30 días)
chage -M 30 "$username"

    # Advertencia 10 días antes
chage -W 10 "$username"

    # Bloqueo después de expirar (0 días de gracia)
chage -I 0 "$username"

    echo "Usuario creado con contraseña por defecto: Abc123*"
    echo "La contrasena debe cambiarse en su primer inicio de sesion."

	# Log de accion
	log_action "Usuario $username creado"

fi

read -p "Presione ENTER para continuar..."
