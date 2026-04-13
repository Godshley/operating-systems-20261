#!/bin/bash

# Cargar logger
source /app/utils/logger.sh

echo "=== ELIMINAR USUARIO ==="

read -p "Ingrese usuario a eliminar: " username

if id "$username" &>/dev/null; then
    userdel -r "$username"
    echo "Usuario eliminado"

# Log de accion
log_action "Usuario $username eliminado"

else
    echo "El usuario no existe"

fi

read -p "Presione ENTER para continuar..."
