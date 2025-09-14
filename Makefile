CC := g++ -std=c++17

MODE ?= release

DEBUG_CCFLAGS := -g -O0 -Wall -Iinclude
RELEASE_CCFLAGS := -O2 -Wall -Iinclude -s

ifeq ($(MODE), debug)
    CCFLAGS := $(DEBUG_CCFLAGS)
else
    CCFLAGS := $(RELEASE_CCFLAGS)
endif

.PHONY: clean all run

SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp, build/%.o, $(SRCS))

OUT := bin/tictactoe.exe

all: $(OUT)

build/%.o : src/%.cpp | build
	$(CC) $(CCFLAGS) -c $< -o $@

$(OUT) : $(OBJS) | bin
	$(CC) $(CCFLAGS) $(OBJS) -o $(OUT)

build:
	if not exist build mkdir build

bin:
	if not exist bin mkdir bin

run: $(OUT)
	./$(OUT)

clean:
	@del /q /f build\*.o bin\*.exe 2>NUL

