CC = gcc
CFLAGS = -Wall -Werror -g
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

SRC_DIR = src
BUILD_DIR = build
TARGET = unigame

SOURCES = $(shell find $(SRC_DIR) -name "*.c")
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(shell mkdir -p $(BUILD_DIR) && ln -srfn assets $(BUILD_DIR)/assets)

clean:
	rm -rf $(TARGET)

.PHONY: all clean
