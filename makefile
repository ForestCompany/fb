CC := gcc
CFLAGS := -std=gnu17 -Wall
LIBS := -lSDL2 -lSDL2_ttf -lSDL2_image -lm -lSDL2_mixer


SRC_DIR := src
EXECUTABLE := executable

SOURCES := $(wildcard $(SRC_DIR)/*.c)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean
clean:
	rm -f $(EXECUTABLE)
	
