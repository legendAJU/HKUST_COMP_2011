# Makefile for Pixel Art Studio Lab
CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = lab5
SOURCES = main.cpp canvas_operations.cpp pattern_generator.cpp art_analyzer.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compile source files to object files
%.o: %.cpp pixel_art.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Test with sample input
test: $(TARGET)
	./$(TARGET) < testcase/pixel_input1.txt

# Show compilation commands
help:
	@echo "Available targets:"
	@echo "  all     - Build the executable"
	@echo "  clean   - Remove object files and executable"
	@echo "  test    - Run with sample input"
	@echo ""
	@echo "Manual compilation:"
	@echo "  g++ -std=c++11 -o lab7 main.cpp canvas_operations.cpp pattern_generator.cpp art_analyzer.cpp"

.PHONY: all clean test help