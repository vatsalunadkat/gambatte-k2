# Toolchain
CC = arm-kindlehf-linux-gnueabihf-gcc
STRIP = arm-kindlehf-linux-gnueabihf-strip

# Compiler flags
CFLAGS = -O3 -march=armv7-a -mtune=cortex-a7 -mfpu=neon -mfloat-abi=hard -mthumb
CFLAGS += -Wall -Wextra -Wno-unused-parameter -I. -pthread
# Force include wrapper to disable static assertions
CFLAGS += -include glib_fix.h

# GTK and X11 include paths (use native Ubuntu headers for compilation)
CFLAGS += -I/usr/include/gtk-2.0
CFLAGS += -I/usr/lib/x86_64-linux-gnu/gtk-2.0/include
CFLAGS += -I/usr/include/pango-1.0
CFLAGS += -I/usr/include/atk-1.0
CFLAGS += -I/usr/include/cairo
CFLAGS += -I/usr/include/gdk-pixbuf-2.0
CFLAGS += -I/usr/include/harfbuzz
CFLAGS += -I/usr/include/glib-2.0
CFLAGS += -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
CFLAGS += -I/usr/include/pixman-1
CFLAGS += -I/usr/include/freetype2
CFLAGS += -I/usr/include/libpng16

# X11 include path added at the end with lower priority
CFLAGS += -idirafter /usr/include

# Linker flags - allow undefined symbols (will be resolved at runtime on Kindle)
LDFLAGS = -Wl,--allow-shlib-undefined -Wl,--unresolved-symbols=ignore-all
LDFLAGS += -ldl -lrt -lm -lpthread -L. -lfbink

# Source files
SOURCES = gambatte-k2.c file_picker.c gray_shm.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = gambatte-k2-armhf

all: $(TARGET)

$(TARGET): $(OBJECTS) libfbink.a
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)
	$(STRIP) $@
	@echo ""
	@echo "========================================="
	@echo "✓ BUILD SUCCESSFUL!"
	@echo "========================================="
	@echo "Binary: $(TARGET)"
	@file $(TARGET)
	@ls -lh $(TARGET)
	@echo ""
	@echo "This binary is cross-compiled for Kindle"
	@echo "and will dynamically link GTK/GLib/etc"
	@echo "at runtime on your Kindle device."
	@echo "========================================="

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
