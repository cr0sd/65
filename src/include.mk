# Include for Makefile to define SDL2 flags based on OS

ifeq ($(OS),Windows_NT)
# Cygwin
CFLAGS		= -DSDL_MAIN_HANDLED -I/mingw64/include
LDFLAGS		= -L/mingw64/lib -lSDL2main -lSDL2 -lpdcurses
else
# Linux/Mac/Unix
ifeq ($(shell uname -s),FreeBSD)
CC			= gcc
ARFLAGS		= rc
CFLAGS		= `pkg-config --cflags sdl2`
LDFLAGS		= `pkg-config --libs sdl2` -lncurses
AS65		= xa65
else
ARFLAGS		= mc
CFLAGS		= `pkg-config --cflags sdl2`
LDFLAGS		= `pkg-config --libs sdl2` -lncurses
endif
endif
