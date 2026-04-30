#!/bin/bash

# Cargar logger
source /app/utils/logger.sh

echo "=== DESBLOQUEAR USUARIO ==="

read -p "Ingrese usuario: " username

if id "$username" &>/dev/null; then
    passwd -u "$username"
    echo "Usuario desbloqueado"

	#log de accion
log_action "Usuario $username desbloqueado"

else
    echo "No existe"
fi

read -p "Presione ENTER para continuar..."
