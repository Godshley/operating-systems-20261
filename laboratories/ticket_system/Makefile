CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

SRC = src/main.c \
      src/utils/utils.c \
      src/ticket/ticket.c

TARGET = ticket_app

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run:	$(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
