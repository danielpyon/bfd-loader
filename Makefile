CC = g++

CFLAGS = --std=c++20 -Wall -Werror -g

TARGET = loader

all: $(TARGET)

$(TARGET): loader.o
	$(CC) $(CFLAGS) -o $(TARGET) loader.o -lbfd

loader.o: loader.cc
	$(CC) $(CFLAGS) -c loader.cc

clean:
	rm -f $(TARGET) *.o

.PHONY: clean
