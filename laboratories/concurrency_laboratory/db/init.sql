CREATE TABLE IF NOT EXISTS input (
    id SERIAL PRIMARY KEY,
    description TEXT NOT NULL,
    status VARCHAR(20) DEFAULT 'pending'
);

CREATE TABLE IF NOT EXISTS result (
    id SERIAL PRIMARY KEY,
    input_id INT REFERENCES input(id) UNIQUE,
    worker_identifier VARCHAR(100) NOT NULL,
    result TEXT NOT NULL,
    date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);