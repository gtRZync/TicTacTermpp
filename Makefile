CC := g++ -std=c++17
CCFLAGS := -O3 -Wall -Iinclude -s
LDFLAGS := -lkernel32 -luser32

.PHONY: clean all run

SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp, build/%.o, $(SRCS))

OUT := bin/tictactoe.exe

all: $(OUT)

build/%.o : src/%.cpp | build
	$(CC) $(CCFLAGS) -c $< -o $@ $(LDFLAGS)

$(OUT) : $(OBJS) | bin
	$(CC) $(CCFLAGS) $(OBJS) -o $(OUT) $(LDFLAGS)

build:
	if not exist build mkdir build

bin:
	if not exist bin mkdir bin

run: $(OUT)
	./$(OUT)

clean:
	@del /q /f build\*.o bin\*.exe 2>NUL

