default: bern-auto-shutdown

CFLAGS += -Wall -Wextra -march=native -Ofast -pipe -flto -fuse-linker-plugin
LDFLAGS += -march=native -Ofast -pipe -flto -fuse-linker-plugin

CC = gcc
#CC = x86_64-w64-mingw32-gcc

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

all: bern-auto-shutdown

bern-auto-shutdown: $(OBJS)
	$(CC) $(OBJS) -o bern-auto-shutdown $(LDFLAGS)

OBJS: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $(SRCS)

clean:
	$(RM) bern-auto-shutdown src/*.o
