# Include for Makefile to define SDL2 flags based on OS

ifeq ($(OS),Windows_NT)
# Cygwin
CFLAGS		= -DSDL_MAIN_HANDLED -I/mingw64/include
LDFLAGS		= -L/mingw64/lib -lSDL2main -lSDL2
else
# Linux/Mac/Unix
CFLAGS		= `pkg-config --cflags sdl2`
LDFLAGS		= `pkg-config --libs sdl2`
endif
