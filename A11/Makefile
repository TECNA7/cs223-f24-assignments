CC = gcc
CFLAGS = -g -Wall -Wvla -Werror -Wno-unused-variable -Wno-unused-but-set-variable
OBJS = tree.o
TARGET = tree_tests
DEPENDENCY_TARGET = dependency
GREPPY = grep

# Main target
all: $(TARGET) $(DEPENDENCY_TARGET) $(GREPPY)

# Target for tree_tests
$(TARGET): tree_tests.c $(OBJS)
	$(CC) $(CFLAGS) tree_tests.c $(OBJS) -o $(TARGET) -lpthread -lreadline

# Target for dependency program
$(DEPENDENCY_TARGET): dependency.c tree.o
	$(CC) $(CFLAGS) dependency.c tree.o -o $(DEPENDENCY_TARGET) -lpthread

# Target for grep program
$(GREPPY): grep.c
	$(CC) $(CFLAGS) grep.c -o $(GREPPY) -lpthread

# Compiling tree.o from tree.c and tree.h
tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c -o tree.o

# Clean up compiled files
clean:
	rm -f $(TARGET) $(OBJS) $(DEPENDENCY_TARGET) $(GREPPY)

