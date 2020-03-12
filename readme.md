[![Build Status](https://travis-ci.com/cr0sd/65.svg?token=WEvCwyPhUBEquCSrRa7q&branch=master)](https://travis-ci.com/cr0sd/65)

### 65

6502 (NES) emulator

A 6502 CPU emulator/simulator with ncurses UI. Includes implementations using video display using either curses or SDL2.

#### Usage

`./65 FILE.NES`

`./65v FILE.NES`

`./65sdl FILE.NES`

#### Building

Dependencies:

65/65v: ncurses / pdcurses (on Windows)

65sdl: SDL2

To build using GNUMake:

	make

To build using Ruby rake

	rake

#### Key bindings:

```
s.........Step into instruction

g.........Goto offset

G.........Toggle follow (to follow CPU PC)

j.........Scroll down through hexdump

k.........Scroll up through hexdump

/.........Search for octet

q.........Quit program
```
