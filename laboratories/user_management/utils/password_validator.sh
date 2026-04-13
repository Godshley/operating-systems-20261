#!/bin/bash

validar_password() {
    local password="$1"

    # Sin espacios
    if [[ "$password" =~ [[:space:]] ]]; then
        echo "La contraseña no debe contener espacios"
        return 1
    fi

    # Al menos una mayúscula
    if [[ ! "$password" =~ [A-Z] ]]; then
        echo "Debe contener al menos una mayúscula"
        return 1
    fi

    # Al menos un caracter especial
    if [[ ! "$password" =~ [^a-zA-Z0-9] ]]; then
        echo "Debe contener al menos un caracter especial"
        return 1
    fi

    return 0
}
