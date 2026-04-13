#!/bin/bash

# Cargar logger
source /app/utils/logger.sh

# Cargar validador
source /app/utils/password_validator.sh

echo "=== CAMBIAR CONTRASEÑA ==="

read -p "Ingrese usuario: " username

# Verificar si existe
if ! id "$username" &>/dev/null; then
    echo "El usuario no existe"
    read -p "Presione ENTER para continuar..."
    exit 1
fi

while true; do
    read -s -p "Nueva contraseña: " password
    echo
    read -s -p "Confirmar contraseña: " password2
    echo

    if [ "$password" != "$password2" ]; then
        echo "Las contraseñas no coinciden"
        continue
    fi

    # Validar contraseña
    validar_password "$password"
    if [ $? -ne 0 ]; then
        continue
    fi

    # Aplicar contraseña
    echo "$username:$password" | chpasswd
#Log de accion
log_action "Contrasena  $password cambiada."

    echo "Contraseña actualizada correctamente"
    break
done

read -p "Presione ENTER para continuar..."
