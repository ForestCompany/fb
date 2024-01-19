CC := gcc
CFLAGS := -std=gnu17 -Wall
LIBS := -lSDL2 -lSDL2_ttf -lSDL2_image -lm

SRC_DIR := source
EXECUTABLE := executable

SOURCES := $(wildcard $(SRC_DIR)/*.c)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean
clean:
	rm -f $(EXECUTABLE)
