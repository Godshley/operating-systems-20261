#!/bin/bash

echo "=== LISTA DE USUARIOS (REALES) ==="

awk -F: '$3 >= 1000 {print $1}' /etc/passwd

read -p "Presione ENTER para continuar..."
