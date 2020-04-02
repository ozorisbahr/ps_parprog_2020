CC = gcc
LD = gcc

OBJ = HelloWorld.o
TARGET = HelloWorld

# TODO add OpenMP flag here
CFLAGS = -fopenmp -O2 -Wall -std=c99
LDLIBS =
INCLUDES =

SRC_DIR =
BUILD_DIR =
VPATH =

# Rules
all: $(TARGET)

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)

.PHONY: clean

# Dependencies
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(TARGET).o -o $(TARGET)
