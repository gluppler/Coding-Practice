CXX := g++

TARGET := donut
SOURCE := donut.cpp
OBJECT := donut.o
DEPFILE := donut.d

CXXFLAGS := \
	-std=c++23 \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Werror \
	-Wconversion \
	-Wsign-conversion \
	-Wshadow \
	-Wformat=2 \
	-Wvla \
	-O2 \
	-g \
	-fsanitize=address,undefined \
	-MMD \
	-MP

LDFLAGS := \
	-fsanitize=address,undefined

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJECT)
	$(CXX) $(LDFLAGS) -o $@ $^

$(OBJECT): $(SOURCE)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPFILE)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJECT) $(DEPFILE)

