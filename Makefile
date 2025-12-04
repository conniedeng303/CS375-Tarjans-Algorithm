CC = g++
CFLAGS = -Wall -O2
TARGET = Tarjan

all: $(TARGET)

$(TARGET): Tarjan.o main.o
	$(CC) $(CFLAGS) -o $@ Tarjan.o

Tarjan.o: Tarjan.cpp
	$(CC) $(CFLAGS) -c Tarjan.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
clean:
	rm -rf *.o $(TARGET)
