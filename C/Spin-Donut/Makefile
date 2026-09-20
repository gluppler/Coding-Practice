CC := gcc

TARGET := donut
SOURCE := donut.c
OBJECT := donut.o

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

LDFLAGS := -fsanitize=address,undefined

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECT)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJECT): $(SOURCE)
	$(CC) $(CFLAGS) -c $< -o $@

-include donut.d

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJECT) donut.d

