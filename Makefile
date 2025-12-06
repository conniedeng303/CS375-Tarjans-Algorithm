CC = g++
CFLAGS = -Wall -O2 -g
TARGET = Tarjan

all: $(TARGET)

$(TARGET): Tarjan.o
	$(CC) $(CFLAGS) -o $@ Tarjan.o

Tarjan.o: Tarjan.cpp
	$(CC) $(CFLAGS) -c Tarjan.cpp

test: $(TARGET)
	./$(TARGET) input.txt output.txt

clean:
	rm -rf *.o $(TARGET)
