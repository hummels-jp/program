CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -pthread
LDFLAGS = -lstdc++fs  # For older gcc versions (pre-9.0)

# Detect GCC version to determine if we need stdc++fs
GCC_VERSION := $(shell $(CXX) -dumpversion)
GCC_MAJOR := $(shell echo $(GCC_VERSION) | cut -d'.' -f1)
ifeq ($(shell expr $(GCC_MAJOR) \>= 9), 1)
    LDFLAGS =  # No need for explicit stdc++fs on GCC 9+
endif

# Target executable
TARGET = cppgrep

# Source files
SRCS = main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean test