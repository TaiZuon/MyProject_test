#OBJS specifies which files to compile as part of the project
OBJS = 01_hello_SDL.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = 01_hello_SDL

#This is the target that compiles our executable
all : $(OBJS)
	g++ $(OBJS) -IC:\Library\SDL2-devel-2.26.3-mingw\SDL2-2.26.3\x86_64-w64-mingw32\include\SDL2 -LC:\Library\SDL2-devel-2.26.3-mingw\SDL2-2.26.3\x86_64-w64-mingw32\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o $(OBJ_NAME)