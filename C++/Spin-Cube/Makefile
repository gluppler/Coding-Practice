CXX := g++

TARGET := cube
SOURCE := cube.cpp
OBJECT := cube.o
DEPFILE := cube.d

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
	-Wold-style-cast \
	-Woverloaded-virtual \
	-Wnon-virtual-dtor \
	-Wconversion-null \
	-O2 \
	-g \
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
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJECT): $(SOURCE)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPFILE)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJECT) $(DEPFILE)

