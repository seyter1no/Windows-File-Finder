# VARIABLES
INCLUDE_DIR = include
SOURCE_DIR = main
BUILD_DIR = build
CXX = g++
CXX_STANDARD = c++17
CXXFLAGS = -Wall -Wextra -Wpedantic -std=$(CXX_STANDARD)
CPPFLAGS = -I $(INCLUDE_DIR)

LIB_NAME = libfile_search.a
LIB_OBJS = $(BUILD_DIR)/file_search.o

# TARGETS
all : create build

create:
	@mkdir -p $(BUILD_DIR)

build: $(LIB_NAME)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) main.cpp -L. -lfile_search -o $(BUILD_DIR)/main

$(LIB_NAME): $(LIB_OBJS)
	ar rcs $(LIB_NAME) $(LIB_OBJS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(INCLUDE_DIR)/%.h
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o
	rm -f $(BUILD_DIR)/main
	rm -f $(LIB_NAME)
