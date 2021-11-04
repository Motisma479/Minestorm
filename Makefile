PROGRAM=minestorm

# Add your objs to generate in OBJS var
OBJS=src/main.o src/game.o src/player.o src/mineLayer.o src/enemy.o src/draw.o src/bullet.o src/Math.o src/levels.o src/input.o src/collision.o

SD = ./src/

OBJS=$(SD)main.o $(SD)game.o $(SD)player.o $(SD)mineLayer.o $(SD)enemy.o $(SD)bullet.o $(SD)draw.o $(SD)Math.o $(SD)collision.o $(SD)levels.o $(SD)input.o

CC=gcc
TARGET=$(shell $(CC) -dumpmachine)

CFLAGS=-O0 -g -Wall -Wextra -Wno-unused-parameter
CPPFLAGS=-Iinclude -Ithird_party/include -MMD
LDFLAGS=-Lthird_party/libs-$(TARGET)
LDLIBS=-lraylib

ifeq ($(TARGET),x86_64-linux-gnu)
LDLIBS+=-ldl -lpthread -lm
else ifeq ($(TARGET),x86_64-pc-cygwin)
LDLIBS+=-lgdi32 -lWinmm -lWs2_32
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
	rm -f $(OBJS) $(DEPS) build.tar.gz $(PROGRAM) $(TEST_COLLISION_C) $(TEST_COLLISION)
