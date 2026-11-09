CC ?= gcc
CFLAGS ?= -std=gnu11 -Wall -Wextra -Iinclude
LDLIBS ?= -lm
BUILD_DIR ?= build

COMMON_SOURCES = src/math/rotation2d.c src/image/rgb_image.c src/io/ppm.c

.PHONY: all blur_image rotate_image clean

all: blur_image rotate_image

blur_image: $(BUILD_DIR)/blur_image

rotate_image: $(BUILD_DIR)/rotate_image

$(BUILD_DIR)/blur_image: examples/blur_image.c $(COMMON_SOURCES) src/image/blur.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIR)/rotate_image: examples/rotate_image.c $(COMMON_SOURCES) src/image/rotate.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -rf $(BUILD_DIR)