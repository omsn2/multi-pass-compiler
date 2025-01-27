# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Ibackend -Ifrontend -Icommon

# Source files
SRC = frontend/main.cpp \
      frontend/editor.cpp \
      frontend/io_window.cpp \
      backend/lexer.cpp \
      backend/parser.cpp \
      backend/type_checker.cpp \
      backend/optimizer.cpp \
      backend/codegen.cpp \
      common/ast.cpp

# Object files
OBJ = frontend/main.o \
      frontend/editor.o \
      frontend/io_window.o \
      backend/lexer.o \
      backend/parser.o \
      backend/type_checker.o \
      backend/optimizer.o \
      backend/codegen.o \
      common/ast.o

# Target executable
TARGET = multi_pass_compiler

# Default target
all: $(TARGET)

# Rule to link object files and create the executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

# Rule to compile individual source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
ifeq ($(OS),Windows_NT)
	@echo "Cleaning up..."
	@if exist *.o del /f /q *.o 2>nul
	@if exist $(TARGET) del /f /q $(TARGET)
else
	@echo "Cleaning up..."
	@rm -f $(OBJ) $(TARGET)
endif

# Phony targets to avoid conflicts with file names
.PHONY: all clean
