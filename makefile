# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Source files
SRCS = main.c dungeon.c player.c inventory.c item.c scenario.c encounter.c trap.c monster.c
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = dungeon_game

# Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Clean up compiled files
clean:
	rm -f $(OBJS) $(TARGET)

# Unit test target
# This is test section for the map section I hope it gives you all some idea of how to do yours
TEST_SRCS = test_game.c dungeon.c
TEST_OBJS = $(TEST_SRCS:.c=.o)
TEST_EXE = test_game

test: $(TEST_EXE)
	./$(TEST_EXE)

$(TEST_EXE): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_EXE) $(TEST_OBJS)