# Include for Makefile to define build flags based on OS

# Use either 'xa' or 'xa65', whichever system provides
AS65		= $(shell `which xa > /dev/null` && echo "xa" || `which xa65 > /dev/null` && echo "xa65")

ifeq ($(OS),Windows_NT)
# Cygwin
CFLAGS		= -DSDL_MAIN_HANDLED -I/mingw64/include
LDFLAGS		= -L/mingw64/lib -lSDL2main -lSDL2 -lpdcurses
else
ifeq ($(shell uname -s),FreeBSD)
# FreeBSD
CC			= gcc
ARFLAGS		= rc
CFLAGS		= `pkg-config --cflags sdl2`
LDFLAGS		= `pkg-config --libs sdl2` -lncurses
RM			= rm -f
else
# Linux/Mac/*nix
ARFLAGS		= mc
CFLAGS		= `pkg-config --cflags sdl2`
LDFLAGS		= `pkg-config --libs sdl2` -lncurses
endif
endif
