require'fileutils'
require'./src/inc.rb'

# Variables
# -----------------------------
$AS65			=	'xa'
$CC				=	'cc'

$stdout_mutex=Mutex.new

# Rules
# -----------------------------
task :default do
	thread_print'Entering directory src'
	thread_print`cd src; rake`
	thread_print'Leaving directory src'
	`mkdir -p bin test`
	thread_print'CP	bin/65db bin/65sdl'
	`cp -p src/65db src/65sdl bin`
	thread_print'CP	test/*.nes'
	`cp -p src/test/*.nes test`
end

task :clean do
	thread_print'Entering directory src'
	thread_print`cd src; rake clean`
	thread_print'Leaving directory src'
	thread_print"RM	bin/65db bin/65sdl test/*.nes"
	`rm bin/65db bin/65sdl test/*.nes`
end
