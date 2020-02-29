require'fileutils'
require'./inc.rb'

# Variables
# -----------------------------
$AS65		=	'xa'
$CC			=	'cc'
$CFLAGS		=	'-Wfatal-errors'
$LDFLAGS	=	'-lncurses'
$OBJS		=	'65.o cpu.o ram.o rom.o disasm.o'

$stdout_mutex=Mutex.new

# Rules
# -----------------------------
task :default => [:_65] do
	
end

task :all => [:_65, :test] do
	
end

task :_65 => [:objs] do
	thread_print"CC\t65"
	`cc #{$CFLAGS} #{$LDFLAGS} #{$OBJS} -o 65`
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
	clean '65 *.nes *.o test/*.nes'.split
end
