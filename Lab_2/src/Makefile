CC := g++
FLAGS := -std=c++17 -Wall -MD -MMD
D_DIR := f_d
OBJ_DIR := f_obj
SRC_DIR := src/
BIN_DIR := bin/
LAUNCHER := file_manager

.PHONY : all
all: compile_c compile_bin makedirs replace
compile_c: $(patsubst %.cpp, %.o, $(wildcard *.cpp))

%.o: %.cpp
	$(CC) $(FLAGS) -c -o $@ $< -lstdc++fs

.PHONY : compile_bin
compile_bin:
	$(CC) $(FLAGS) $(wildcard *.o) -o $(LAUNCHER) -lstdc++fs

.PHONY : makedirs
makedirs:
	mkdir -p f_d f_obj bin 

.PHONY : replace
replace:
	mv *.d $(D_DIR) && mv *.o $(OBJ_DIR) && mv $(LAUNCHER) $(BIN_DIR)

.PHONY : clean
clean:
	rm -r $(BIN_DIR) $(D_DIR) $(OBJ_DIR)
