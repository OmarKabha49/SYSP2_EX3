# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -g

# Include directories
INCLUDES = -I.

# Source files for the main executable
MAIN_SRCS = board.cpp catan.cpp player.cpp launch.cpp

# Source files for the test executables
TEST_SRCS_BOARD = board.cpp player.cpp testBoard.cpp
TEST_SRCS_PLAYER = player.cpp testPlayer.cpp
TEST_SRCS_CATAN = board.cpp catan.cpp player.cpp testCatan.cpp

# Object files
MAIN_OBJS = $(MAIN_SRCS:.cpp=.o)
TEST_OBJS_BOARD = $(TEST_SRCS_BOARD:.cpp=.o)
TEST_OBJS_PLAYER = $(TEST_SRCS_PLAYER:.cpp=.o)
TEST_OBJS_CATAN = $(TEST_SRCS_CATAN:.cpp=.o)

# Executables
EXEC = catan_game
TEST_EXEC_BOARD = test_board
TEST_EXEC_PLAYER = test_player
TEST_EXEC_CATAN = test_catan

# Target to compile all executables
all: $(EXEC) $(TEST_EXEC_BOARD) $(TEST_EXEC_PLAYER) $(TEST_EXEC_CATAN)

# Target to compile the main executable
$(EXEC): $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

# Target to compile the test executable for board
$(TEST_EXEC_BOARD): $(TEST_OBJS_BOARD)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

# Target to compile the test executable for player
$(TEST_EXEC_PLAYER): $(TEST_OBJS_PLAYER)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

# Target to compile the test executable for catan
$(TEST_EXEC_CATAN): $(TEST_OBJS_CATAN)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean target to remove compiled files
clean:
	rm -f $(MAIN_OBJS) $(TEST_OBJS_BOARD) $(TEST_OBJS_PLAYER) $(TEST_OBJS_CATAN) $(EXEC) $(TEST_EXEC_BOARD) $(TEST_EXEC_PLAYER) $(TEST_EXEC_CATAN)

# Phony targets
.PHONY: all clean
