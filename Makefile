CC = clang++

CFLAGS = --std=c++20 -Wall -Werror -g

TARGET = loader

all: $(TARGET)

$(TARGET): loader.o
	$(CC) $(CFLAGS) -o $(TARGET) loader.o

loader.o: loader.cc
	$(CC) $(CFLAGS) -c loader.cc

clean:
	rm -f $(TARGET) *.o

.PHONY: clean
