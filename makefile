#OBJS specifies which files to compile as part of the project
OBJS = bin/main.o bin/joystick.o bin/perifericos.o bin/Renderizador.o bin/sdlutil.o bin/tela.o bin/Frequent.o

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = `sdl2-config --cflags --libs` -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

#This is the target that compiles our executable
TARG_bin = bin/

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

bin/%.o : src/%.cpp
	$(CC) $< $(COMPILER_FLAGS) $(LINKER_FLAGS) -c -o $@


clean:
	rm bin/*
	rm $(OBJ_NAME)