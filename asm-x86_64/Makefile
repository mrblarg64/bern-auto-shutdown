default: bern-auto-shutdown

CFLAGS += -Wall -Wextra -march=native -Ofast -pipe -flto -fuse-linker-plugin
LDFLAGS += -march=native -Ofast -pipe -flto -fuse-linker-plugin

AS = as
LD = ld
#CC = gcc
#CC = x86_64-w64-mingw32-gcc

SRCS = $(wildcard src/*.s)
OBJS = $(SRCS:.s=.o)

all: bern-auto-shutdown

bern-auto-shutdown: $(OBJS)
	$(LD) -o bern-auto-shutdown $(OBJS)

OBJS: $(SRCS)
	$(AS) -o $@ $(SRCS)

clean:
	$(RM) bern-auto-shutdown src/*.o
