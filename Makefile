# commands:
# make - compiles the source files and generates the executable
# make run - runs the executable and generates the output.ppm file
# make clean - removes the build files and the output.ppm file


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
	del /Q $(OBJS) $(TARGET).exe output.ppm 2>NUL || echo Files already cleaned

.PHONY: all clean run