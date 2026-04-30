#!/bin/bash

if [ "$EUID" -ne 0 ]; then
    echo "Este sistema debe ejecutarse con sudo o como root"
    exit 1
fi

# ==============================
# Sistema de Administración de Usuarios
# ==============================

while true; do
    clear
    echo "====================================="
    echo "  SISTEMA DE ADMINISTRACIÓN DE USUARIOS"
    echo "====================================="
    echo "1. Crear usuario"
    echo "2. Listar usuarios"
    echo "3. Bloquear usuario"
    echo "4. Desbloquear usuario"
    echo "5. Eliminar usuario"
    echo "6. Cambiar contrasena"
    echo "7. Salir"
    echo "====================================="

    read -p "Seleccione una opción: " opcion

    case $opcion in
        1)
            bash modules/user_create.sh
            ;;
        2)
            bash modules/user_list.sh
            ;;
        3)
            bash modules/user_lock.sh
            ;;
        4)
            bash modules/user_unlock.sh
            ;;
        5)
            bash modules/user_delete.sh
            ;;
        6)
            bash modules/user_passwd.sh
            ;;
        7)
            echo "Saliendo..."
            exit 0
            ;;
        *)
            echo "Opción inválida"
            sleep 2
            ;;
    esac
done
