FROM python:3.12-slim

WORKDIR /app

# Copiar e instalar dependencias
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

# Copiar el script del worker
COPY worker.py .

# Comando de ejecución
CMD ["python", "worker.py"]