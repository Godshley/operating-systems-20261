import os
import time
import psycopg2
import socket
from datetime import datetime

WORKER_ID = os.environ.get("WORKER_ID", socket.gethostname())

DB_CONFIG = {
    "host": os.environ.get("DB_HOST", "localhost"),
    "port": os.environ.get("DB_PORT", "5432"),
    "database": os.environ.get("DB_NAME", "concurrencia"),
    "user": os.environ.get("DB_USER", "admin"),
    "password": os.environ.get("DB_PASSWORD", "admin123"),
}

SHARED_LOG = os.environ.get("SHARED_LOG", "/shared/activity.log")


def log(mensaje):
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]
    linea = f"[{timestamp}] [{WORKER_ID}] {mensaje}"
    print(linea, flush=True)
    try:
        import fcntl
        os.makedirs(os.path.dirname(SHARED_LOG), exist_ok=True)
        with open(SHARED_LOG, "a", encoding="utf-8") as f:
            fcntl.flock(f.fileno(), fcntl.LOCK_EX)
            f.write(linea + "\n")
            f.flush()
            os.fsync(f.fileno())          # garantiza escritura real en disco
            fcntl.flock(f.fileno(), fcntl.LOCK_UN)
    except Exception:
        pass


def obtener_tarea(conn):
    try:
        with conn.cursor() as cur:
            cur.execute("""
                WITH picked AS (
                    SELECT id, description
                    FROM input
                    WHERE status = 'pending'
                    ORDER BY id
                    LIMIT 1
                    FOR UPDATE SKIP LOCKED
                )
                UPDATE input AS i
                SET status = 'in_process'
                FROM picked
                WHERE i.id = picked.id
                RETURNING picked.id, picked.description;
            """)
            tarea = cur.fetchone()
            conn.commit()
            return tarea
    except Exception as e:
        conn.rollback()
        log(f"Error al obtener tarea: {e}")
        return None


def procesar_tarea(input_id, description):
    log(f"Procesando tarea ID={input_id}: {description}")
    tiempo = 0.5 + (hash(description) % 10) / 10.0
    time.sleep(tiempo)
    return f"Completado en {tiempo:.1f}s por {WORKER_ID}"


def guardar_resultado(conn, input_id, resultado):
    try:
        with conn.cursor() as cur:
            # ON CONFLICT: si otro worker ya insertó este input_id, no falla
            cur.execute("""
                INSERT INTO result (input_id, worker_identifier, result)
                VALUES (%s, %s, %s)
                ON CONFLICT (input_id) DO NOTHING
                RETURNING id;
            """, (input_id, WORKER_ID, resultado))

            fila = cur.fetchone()

            cur.execute(
                "UPDATE input SET status = 'processed' WHERE id = %s",
                (input_id,)
            )
            conn.commit()
            return fila[0] if fila else None
    except Exception as e:
        conn.rollback()
        log(f"Error al guardar resultado ID={input_id}: {e}")
        return None


def main():
    log("Worker iniciado. Conectando a la base de datos...")

    conn = None
    for intento in range(30):
        try:
            conn = psycopg2.connect(**DB_CONFIG)
            log("Conexión exitosa a la base de datos.")
            break
        except psycopg2.OperationalError:
            log(f"BD no disponible, reintentando ({intento + 1}/30)...")
            time.sleep(2)

    if conn is None:
        log("ERROR: No se pudo conectar a la BD.")
        return

    procesadas = 0
    while True:
        tarea = obtener_tarea(conn)
        if tarea is None:
            log(f"No hay más tareas pendientes. Total procesadas: {procesadas}")
            break

        input_id, description = tarea
        resultado = procesar_tarea(input_id, description)
        result_id = guardar_resultado(conn, input_id, resultado)

        if result_id:
            procesadas += 1
            log(f"✓ Tarea ID={input_id} completada. Resultado guardado con ID={result_id}")

    conn.close()
    log("Worker finalizado.")


if __name__ == "__main__":
    main()