#all:
#	g++ -std=c++14 -I include -L lib -o build/main src/main.cpp -lmingw32 -lSDL2 -lSDL2main

# Directories
S_DIR=src
B_DIR=build

# Files
S_FILES=$(S_DIR)/*.cpp $(S_DIR)/*.hpp

# Output
EXEC=$(B_DIR)/SDLGame

# Build settings
CC=g++ -Wall -w -std=c++14 -I include -L lib
# SDL options
CC_SDL=-lmingw32 -lSDL2 -lsdl2_ttf -lSDL2main -lSDL2_image


all:
	$(CC) $(S_FILES) -o $(EXEC) $(CC_SDL)
# $(CC) $(S_FILES) -o $(EXEC) $(CC_SDL) && start build/SDLGame.exe