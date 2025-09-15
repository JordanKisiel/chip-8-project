#specify file to compile as part of project
OBJS = basic_window.c

#specify compiler
CC = gcc

#specify the additional compilation options
# -w suppresses all warnings
COMPILER_FLAGS = -w

#specify the libraries we're linking against
LINKER_FLAGS = -lSDL2

#specify the name our executable
OBJ_NAME = basic_window

#target that compiles executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
