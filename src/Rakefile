require'fileutils'
require'./inc.rb'

# Variables
# -----------------------------
$AS65			=	'xa'
$CC				=	'cc'
$CFLAGS			=	'-Wfatal-errors'
$LDFLAGS		=	'-lncurses -pthread -lpthread'
$SDL2_CFLAGS	=	'`pkg-config --cflags sdl2`'
$SDL2_LDFLAGS	=	'`pkg-config --libs sdl2`'
$OBJS			=	'cpu.o ram.o rom.o joy.o vis.o disasm.o'

$stdout_mutex=Mutex.new

# Rules
# -----------------------------
task :default => [:_65] do
	
end

task :all => [:_65, :_65v, :_65sdl, :test] do
	
end

task :_65 => [:objs] do
	thread_print"CC\t65"
	`cc #{$CFLAGS} 65.c #{$LDFLAGS} #{$OBJS} -o 65`
end

task :_65v => [:objs] do
	thread_print"CC\t65v"
	`cc #{$CFLAGS} 65v.c #{$LDFLAGS} #{$OBJS} -o 65v`
end

task :_65sdl => [:objs] do
	thread_print"CC\t65sdl"
	`cc #{$CFLAGS} 65sdl.c #{$SDL2_LDFLAGS} sdl.c #{$SDL2_CFLAGS} #{$LDFLAGS} #{$OBJS} -o 65sdl`
end

task :test do
	thread_print'Entering directory test'
	thread_print`cd test; rake`
	thread_print'Leaving directory test'
end

task :objs do
	make $OBJS.split
end

task :clean do
	clean '65 65v 65sdl *.nes *.o test/*.nes'.split
end
