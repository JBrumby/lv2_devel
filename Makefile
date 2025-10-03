# Compiler and flags
CC = gcc
CFLAGS = -std=c99 -fPIC -Wall -Wextra
DEBUG_CFLAGS = -g -DDEBUG -O0
RELEASE_CFLAGS = -O2 -DNDEBUG
LDFLAGS = -shared -lm
LV2_PATH = /zynthian/zynthian-plugins/lv2

# Source files
SOURCES = src/scale_quantizer.c
HEADERS = src/scale_quantizer.h
TARGET = scale_quantizer.so

# LV2 includes
LV2_INCLUDES = -I/usr/include/lv2 -I/usr/local/include/lv2

# Build directory
BUILD_DIR = build
PLUGIN_DIR = $(BUILD_DIR)/scale-quantizer.lv2

# Default build (release)
all: CFLAGS += $(RELEASE_CFLAGS)
all: $(BUILD_DIR) $(TARGET)

# Debug build
debug: CFLAGS += $(DEBUG_CFLAGS)
debug: $(BUILD_DIR) $(TARGET)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(PLUGIN_DIR)

# Compile plugin
$(TARGET): $(BUILD_DIR) $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(LV2_INCLUDES) $(SOURCES) -o $(PLUGIN_DIR)/$(TARGET) $(LDFLAGS)
	cp manifest.ttl $(PLUGIN_DIR)/
	cp scale_quantizer.ttl $(PLUGIN_DIR)/

# Install to system LV2 directory
install: all
	mkdir -p $(LV2_PATH)/scale-quantizer.lv2
	cp $(PLUGIN_DIR)/* $(LV2_PATH)/scale-quantizer.lv2/

# Clean build
clean:
	rm -rf $(BUILD_DIR)

# Run tests
test: debug
	LV2_PATH=$(CURDIR)/$(BUILD_DIR) jalv https://github.com/JBrumby/scale-quantizer

# Alternative: Test mit jalv
test-run: debug
	@echo "Starting plugin (will timeout after 5 seconds)..."
	@timeout 5 bash -c 'LV2_PATH=$(CURDIR)/$(BUILD_DIR) jalv https://github.com/JBrumby/scale-quantizer' || true
	@echo "Test completed"

gdb: debug
	LV2_PATH=$(CURDIR)/$(BUILD_DIR) cgdb --args jalv https://github.com/JBrumby/scale-quantizer


.PHONY: all debug install clean test
