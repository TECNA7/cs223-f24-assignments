CC=gcc
SOURCES=search warmup shell
FILES := $(subst .c,,$(SOURCES))
FLAGS=-g -Wall -Wvla -Werror -Wno-unused-variable -Wno-unused-but-set-variable

# By default, make runs the first target in the file
all: $(FILES)

# Rule to compile search and warmup with read_ppm.c and write_ppm.c
%: %.c read_ppm.c write_ppm.c
	$(CC) $(FLAGS) $< read_ppm.c write_ppm.c -o $@

# Rule to compile shell separately with readline library
shell: shell.c
	$(CC) $(FLAGS) shell.c -lreadline -o shell

clean:
	rm -rf $(FILES)

