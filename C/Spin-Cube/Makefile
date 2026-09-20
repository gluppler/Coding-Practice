CC := gcc

TARGET := cube
SOURCE := cube.c
OBJECT := cube.o
DEPFILE := cube.d

CFLAGS := \
	-std=c23 \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Werror \
	-Wconversion \
	-Wsign-conversion \
	-Wshadow \
	-Wstrict-prototypes \
	-Wmissing-prototypes \
	-Wold-style-definition \
	-Wundef \
	-Wcast-qual \
	-Wcast-align \
	-Wwrite-strings \
	-Wformat=2 \
	-Wnull-dereference \
	-Wdouble-promotion \
	-Wvla \
	-Wswitch-enum \
	-O2 \
	-g \
	-fno-common \
	-fsanitize=address,undefined \
	-MMD \
	-MP

LDFLAGS := \
	-fsanitize=address,undefined

LDLIBS := \
	-lm

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJECT)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJECT): $(SOURCE)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPFILE)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJECT) $(DEPFILE)

