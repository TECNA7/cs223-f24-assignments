CC = gcc
SOURCES = bitmap.c decode.c encode.c
FILES = $(SOURCES:.c=)
FLAGS = -g -Wall -Wvla -Werror -Wno-unused-variable -Wno-unused-but-set-variable

all: $(FILES)

%: %.c read_ppm.c write_ppm.c
	$(CC) $(FLAGS) $< read_ppm.c write_ppm.c -o $@

clean:
	rm -f $(FILES)

