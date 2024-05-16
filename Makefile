CC=g++
CFLAGS= -std=c++20
BUILD_DIR := build
PROJ_NAME := out

ray-trace:
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) src/main.cpp -o $(BUILD_DIR)/$(PROJ_NAME)
	$(BUILD_DIR)/out

clean:
	rm -rf build