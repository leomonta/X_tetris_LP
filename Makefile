CC=gcc
BinName=bin/Game.bin
ObjsDir=objs

# Debug variables
DCompilerArgs=-g3 -ansi -pedantic-errors -Wno-missing-field-initializers -Wpedantic -Wconversion -Wshadow -Wextra -fsanitize=address -fsanitize=pointer-compare -fsanitize=pointer-subtract -fsanitize=leak
DLinkerArgs=-fsanitize=address -fsanitize=pointer-compare -fsanitize=pointer-subtract -fsanitize=leak
DLibrariesPaths=-Lext/raylib/lib
DLibrariesNames=-lraylib -ldl -lpthread -lm

# Release variables
RCompilerArgs=-O2 -ansi -pedantic-errors
RLinkerArgs=-O2
RLibrariesPaths=-Lext/raylib/lib
RLibrariesNames=-lraylib -ldl -lpthread -lm

# includes
Includes=-Iinclude -Iext


debug: DCompile DLink

release: RCompile RLink


DCompile: 
	$(CC) $(DCompilerArgs) $(Includes) -c -o $(ObjsDir)/srcmultiplayer.o src/multiplayer.c
	$(CC) $(DCompilerArgs) $(Includes) -c -o $(ObjsDir)/srctetramino.o src/tetramino.c
	$(CC) $(DCompilerArgs) $(Includes) -c -o $(ObjsDir)/srcconstants.o src/constants.c
	$(CC) $(DCompilerArgs) $(Includes) -c -o $(ObjsDir)/srcutils.o src/utils.c
	$(CC) $(DCompilerArgs) $(Includes) -c -o $(ObjsDir)/srcgraphics.o src/graphics.c
	$(CC) $(DCompilerArgs) $(Includes) -c -o $(ObjsDir)/srcsingleplayer.o src/singleplayer.c
	$(CC) $(DCompilerArgs) $(Includes) -c -o $(ObjsDir)/srcmain.o src/main.c

DLink: 
	$(CC) $(DLinkerArgs) -o $(BinName) $(DLibrariesPaths) $(ObjsDir)/srcmultiplayer.o $(ObjsDir)/srctetramino.o $(ObjsDir)/srcconstants.o $(ObjsDir)/srcutils.o $(ObjsDir)/srcgraphics.o $(ObjsDir)/srcsingleplayer.o $(ObjsDir)/srcmain.o $(DLibrariesNames)

RCompile: 
	$(CC) $(RCompilerArgs) $(Includes) -c -o $(ObjsDir)/srcmultiplayer.o src/multiplayer.c
	$(CC) $(RCompilerArgs) $(Includes) -c -o $(ObjsDir)/srctetramino.o src/tetramino.c
	$(CC) $(RCompilerArgs) $(Includes) -c -o $(ObjsDir)/srcconstants.o src/constants.c
	$(CC) $(RCompilerArgs) $(Includes) -c -o $(ObjsDir)/srcutils.o src/utils.c
	$(CC) $(RCompilerArgs) $(Includes) -c -o $(ObjsDir)/srcgraphics.o src/graphics.c
	$(CC) $(RCompilerArgs) $(Includes) -c -o $(ObjsDir)/srcsingleplayer.o src/singleplayer.c
	$(CC) $(RCompilerArgs) $(Includes) -c -o $(ObjsDir)/srcmain.o src/main.c

RLink: 
	$(CC) $(RLinkerArgs) -o $(BinName) $(RLibrariesPaths) $(ObjsDir)/srcmultiplayer.o $(ObjsDir)/srctetramino.o $(ObjsDir)/srcconstants.o $(ObjsDir)/srcutils.o $(ObjsDir)/srcgraphics.o $(ObjsDir)/srcsingleplayer.o $(ObjsDir)/srcmain.o $(RLibrariesNames)

clean:
	rm -r -f objs/*
	rm -r -f $(BinName)
