CC := clang
CFLAGS := -std=c11 -Wall -Wextra -Werror -Wpedantic
LIBS := -lSDL2 -lSDL2_ttf -lSDL2_image -lm -lSDL2_mixer


SRC_DIR := src
EXECUTABLE := endgame

SOURCES := $(wildcard $(SRC_DIR)/*.c)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean
clean:
	rm -f $(EXECUTABLE)
