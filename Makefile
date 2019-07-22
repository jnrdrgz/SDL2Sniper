# A simple Makefile for compiling small SDL projects

# set the compiler
CC := g++

# set the compiler flags
CFLAGS := `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# add header files here
HDRS := Aim.h Bullet.h Constants.h Enemy.h Game.h Machete.h Menu.h MenuItem.h Particles.h TextureManager.h Audio.h

# add source files here
SRCS := Aim.cpp Bullet.cpp Enemy.cpp Game.cpp Machete.cpp main.cpp Menu.cpp MenuItem.cpp Particles.cpp TextureManager.cpp Audio.cpp

# generate names of object files
OBJS := $(SRCS:.c=.o)

# name of executable
EXEC := game

# default recipe
all: $(EXEC)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# recipe for building object files
#$(OBJS): $(@:.o=.c) $(HDRS) Makefile
#	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean
