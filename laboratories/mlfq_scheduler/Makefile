CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

SRC = \
src/main.c \
src/process/process.c \
src/queue/queue.c \
src/scheduler/scheduler.c \
src/metrics/metrics.c

TARGET = mlfq_test

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
