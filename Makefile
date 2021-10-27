PROGRAM=minestorm
TEST_COLLISION = test_collision

# Add your objs to generate in OBJS var

SD = ./src/

OBJS=$(SD)main.o $(SD)game.o $(SD)player.o $(SD)mineLayer.o $(SD)enemy.o $(SD)bullet.o $(SD)draw.o $(SD)Math.o $(SD)collision.o $(SD)levels.o

CC=gcc
TARGET=$(shell $(CC) -dumpmachine)

CFLAGS=-O0 -g -Wall -Wextra -Wno-unused-parameter
CPPFLAGS=-Iinclude -Ithird_party/include -MMD
LDFLAGS=-Lthird_party/libs-$(TARGET)
LDLIBS=-lraylib

ifeq ($(TARGET),x86_64-linux-gnu)
LDLIBS+=-ldl -lpthread -lm
#else ifeq ($(TARGET),x86_64-pc-cygwin)
LDLIBS+=-lgdi32 -lWinmm -lWs2_32
endif

DEPS=$(OBJS:.o=.d)

.PHONY: all clean

all: $(PROGRAM)  $(TEST_COLLISION)

-include $(DEPS)

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(TEST_COLLISION): ./src/test.o ./src/Math.o ./src/collision.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@
build.tar.gz: $(PROGRAM) $(wildcard assets/*)
	tar czf build.tar.gz $(PROGRAM) assets

clean:
	rm -f $(OBJS) $(DEPS) build.tar.gz $(PROGRAM)