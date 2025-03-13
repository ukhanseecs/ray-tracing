# Compiler settings
CXX = g++
CXXFLAGS = -Wall -O2 -std=c++17

# Output executable name
TARGET = raytracing

# Source files
SRCS = raytracing.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Run target to generate PPM output
run: $(TARGET)
	$(TARGET) > output.ppm

# Compilation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET) output.ppm

.PHONY: all clean run