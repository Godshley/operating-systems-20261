#!/bin/bash

log_action() {
    local mensaje="$1"
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $mensaje" >> /app/logs/actions.log
}
