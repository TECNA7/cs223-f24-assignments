CC = gcc
CFLAGS = -g -Wall -Wvla -Werror -Wno-unused-variable -Wno-unused-but-set-variable
OBJS = tree.o
TARGET = tree_tests

all: $(TARGET)

$(TARGET): tree_tests.c $(OBJS)
	$(CC) $(CFLAGS) tree_tests.c $(OBJS) -o $(TARGET) -lpthread -lreadline

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c -o tree.o

clean:
	rm -f $(TARGET) $(OBJS)

