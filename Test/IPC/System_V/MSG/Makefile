C = gcc
CFLAGS = -g -Wall -O2

src = $(wildcard *.c)
target = $(patsubst %.c, %, $(src))

.PHONY:all clean

all:$(target)

%:%.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(target)

