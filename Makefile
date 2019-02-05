CC=clang
CPPCHECK=C:\Program Files\Cppcheck\cppcheck.exe
CFLAGS=-Wall -Werror -Iinclude -Wno-pragma-pack
LDFLAGS=-L. -lSDL2
BINARY=tetris
BINARY_TESTS=tetris_tests

ifeq ($(OS),Windows_NT)
	BINARY:=$(BINARY).exe
	BINARY_TESTS:=$(BINARY_TESTS).exe
endif

tetris: main.o tetris.o gfx.o inputs.o math.o audio.o
	$(CC) -o $(BINARY) $(LDFLAGS) $^

main.o: main.c
	$(CC) -c -o $@ $(CFLAGS) $^
	$(CPPCHECK) $^

tetris.o: tetris.c tetris.h
	$(CC) -c -o $@ $(CFLAGS) $<
	$(CPPCHECK) $^

tests.o: tests.c
	$(CC) -c -o $@ $(CFLAGS) $^
	$(CPPCHECK) $^

gfx.o: gfx.c tetris.h
	$(CC) -c -o $@ $(CFLAGS) $<
	$(CPPCHECK) $^

inputs.o: inputs.c tetris.h
	$(CC) -c -o $@ $(CFLAGS) $<
	$(CPPCHECK) $^

math.o: math.c tetris.h
	$(CC) -c -o $@ $(CFLAGS) $<
	$(CPPCHECK) $^

audio.o: audio.c tetris.h audio.h
	$(CC) -c -o $@ $(CFLAGS) $<
	$(CPPCHECK) $^

test: tests.o tetris.o
	$(CC) -o $(BINARY_TESTS) $(LDFLAGS) $^
	./$(BINARY_TESTS)
