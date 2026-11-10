CC ?= gcc
CFLAGS ?= -std=gnu11 -Wall -Wextra -Iinclude
LDLIBS ?= -lm
BUILD_DIR ?= build

IMAGE_PROPERTY_SOURCES = src/image/image_properties.c src/image/image_type/ppm.c
RGB_IMAGE_SOURCES = src/image/color_properties/rgb_image.c
GRAY_IMAGE_SOURCES = src/image/color_properties/gray_image.c
ROTATION_SOURCES = src/geometry/geometric_transformations/rotation2d.c

.PHONY: all blur_image rotate_image convert_gray_image detect_edges clean

all: blur_image rotate_image convert_gray_image detect_edges

blur_image: $(BUILD_DIR)/blur_image

rotate_image: $(BUILD_DIR)/rotate_image

convert_gray_image: $(BUILD_DIR)/convert_gray_image

detect_edges: $(BUILD_DIR)/detect_edges

$(BUILD_DIR)/blur_image: examples/blur_image.c $(IMAGE_PROPERTY_SOURCES) $(RGB_IMAGE_SOURCES) $(GRAY_IMAGE_SOURCES) src/image/filters/rgb/blur.c src/image/filters/gray/blur.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIR)/rotate_image: examples/rotate_image.c $(IMAGE_PROPERTY_SOURCES) $(RGB_IMAGE_SOURCES) $(ROTATION_SOURCES) src/image/geometric_transformations/rotate.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIR)/convert_gray_image: examples/convert_gray_image.c $(IMAGE_PROPERTY_SOURCES) $(RGB_IMAGE_SOURCES) $(GRAY_IMAGE_SOURCES)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIR)/detect_edges: examples/detect_edges.c $(IMAGE_PROPERTY_SOURCES) $(GRAY_IMAGE_SOURCES) src/image/filters/gray/edge_detector.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -rf $(BUILD_DIR)