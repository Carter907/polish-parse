CC = gcc
CD = gdb

PROG = revpolish
SOURCES = src/*.c

VER = c23

BUILD_DIR= ./build

CFLAGS = -std=$(VER) -g -Wall -Werror -Wconversion -fsanitize=undefined,leak

run: build
	$(BUILD_DIR)/$(PROG)

build: $(SOURCES) 
	mkdir -p $(BUILD_DIR)
	$(CC) -o $(PROG) $(CFLAGS) $(SOURCES)
	mv $(PROG) $(BUILD_DIR) 

format:
	clang-format -i $(SOURCES)

clean:
	rm -rf $(BUILD_DIR)

debug: build
	$(CD) $(BUILD_DIR)/$(PROG)
