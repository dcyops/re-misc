# Define compiler
CC = gcc

# Define any compile-time flags
CFLAGS = -Wall -Werror -g

# Define the target executable
TARGET = poc

# Define objects
OBJS = main.o find_files.o inspect_files.o

# 'all' target
all: $(TARGET)

# Linking all objects to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	rm -rf $(OBJS)

# Compiling main.c to main.o
main.o: main.c main.h find_files.h inspect_files.h
	$(CC) $(CFLAGS) -c main.c

# Compiling find_files.c to find_files.o
find_files.o: find_files.c find_files.h
	$(CC) $(CFLAGS) -c find_files.c

# Compiling inspect_files.c to inspect_files.o
inspect_files.o: inspect_files.c inspect_files.h
	$(CC) $(CFLAGS) -c inspect_files.c

# 'clean' target for cleaning up
clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: all clean

