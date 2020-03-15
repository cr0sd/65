# Include for Makefile to define SDL2 flags based on OS

ifeq ($(OS),Windows_NT)
# Cygwin
SDL2_CFLAGS		= -DSDL_MAIN_HANDLED -I/mingw64/include
SDL2_LDFLAGS	= -L/mingw64/lib -lSDL2main -lSDL2
else
# Linux/Mac/Unix
SDL2_CFLAGS		= `pkg-config --cflags sdl2`
SDL2_LDFLAGS	= `pkg-config --libs sdl2`
endif
