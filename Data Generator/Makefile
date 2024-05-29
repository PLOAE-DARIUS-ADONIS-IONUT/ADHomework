CC = gcc
CFLAGS = -Wall -Wextra

SRCS = main.c
OBJS = $(SRCS:.c=.o)
EXEC = lobster_generator.exe

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	del /Q $(OBJS) $(EXEC)
