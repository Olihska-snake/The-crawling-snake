CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = snake
OBJS = main.o snake.o render.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c snake.h
	$(CC) $(CFLAGS) -c main.c

snake.o: snake.c snake.h
	$(CC) $(CFLAGS) -c snake.c

render.o: render.c snake.h
	$(CC) $(CFLAGS) -c render.c

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)