CC := g++
FLAGS := -std=c++17 -Wall
SRC_DIR := src/
LAUNCHER := file_manager

.PHONY : all
all: compile

.PHONY : compile
compile:
	$(CC) $(FLAGS) $(wildcard $(SRC_DIR)*.cpp) -o $(LAUNCHER) -lstdc++fs

.PHONY : clean
clean:
	rm -r $(LAUNCHER)
