#!/bin/bash

#Cargar logger

source /app/utils/logger.sh

echo "=== BLOQUEAR USUARIO ==="

read -p "Ingrese usuario: " username

if id "$username" &>/dev/null; then
    passwd -l "$username"
    echo "Usuario bloqueado"

# Log de accion
log_action "Usuario $username bloqueado"

else
    echo "No existe"
fi

read -p "Presione ENTER para continuar..."
