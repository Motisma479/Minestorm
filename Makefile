PROGRAM=minestorm

# Add your objs to generate in OBJS var


OBJS=src/main.o src/game.o src/player.o src/mineLayer.o src/enemy.o src/bullet.o src/Math.o

#SD = /home/ISART/v.caraulan/Work/minestorm/src/

SD = ./src/
SRC= $(SD)main.c $(SD)game.c $(SD)player.c $(SD)enemy.c $(SD)bullet.c $(SD)Math.c $(SD)draw.c
OBJS= $(SD)main.o $(SD)game.o $(SD)player.o $(SD)enemy.o $(SD)bullet.o $(SD)Math.o $(SD)draw.o
#OBJS = $(SRC:$(SD)%.c=$(SD)%.o)
CC=gcc
TARGET=$(shell $(CC) -dumpmachine)

CFLAGS=-O0 -g -Wall -Wextra -Wno-unused-parameter -Isrc #-fsanitize=address
CPPFLAGS=-Iinclude -Ithird_party/include -MMD
LDFLAGS=-Lthird_party/libs-$(TARGET)
LDLIBS=-lraylib

ifeq ($(TARGET),x86_64-linux-gnu)
LDLIBS+=-ldl -lpthread -lm
else ifeq ($(TARGET),x86_64-pc-cygwin)
LDLIBS+=-lgdi32
endif

DEPS=$(OBJS:.o=.d)

.PHONY: all clean

all: $(PROGRAM)

-include $(DEPS)

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

build.tar.gz: $(PROGRAM) $(wildcard assets/*)
	tar czf build.tar.gz $(PROGRAM) assets

clean:
	rm -f $(OBJS) $(DEPS) build.tar.gz $(PROGRAM)