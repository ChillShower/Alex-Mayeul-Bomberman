CC = gcc
CFLAGS = -Wall -Iinclude

SRC_DIR = source
INC_DIR = include
MAIN_DIR = main
TEST_DIR = test
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(SRC_FILES))

all: my_executable

my_executable: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $(MAIN_DIR)/main.c $(OBJ_FILES) `sdl2-config --cflags --libs` -lSDL2_image -lxcb

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c 
	$(CC) $(CFLAGS) -c $< -o $@ `sdl2-config --cflags --libs` -lSDL2_image -lxcb

test: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o test_exec/$@ $(TEST_DIR)/test.c $(OBJ_FILES) `sdl2-config --cflags --libs` -lSDL2_image -lxcb

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ `sdl2-config --cflags --libs` -lSDL2_image -lxcb

test-mayeul: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o test_exec/$@ $(TEST_DIR)/test-mayeul.c $(OBJ_FILES) `sdl2-config --cflags --libs` -lSDL2_image -lxcb

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ `sdl2-config --cflags --libs` -lSDL2_image -lxcb

clean:
	rm -f $(OBJ_FILES) my_executable test_exec/test