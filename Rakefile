require'fileutils'
require'./src/include.rb'

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
	thread_print'  CP	bin/65db bin/fes'
	`cp -p src/65db src/fes bin`
	thread_print'  CP	test/*.nes'
	`cp -p src/test/*.nes test`
end

task :clean do
	thread_print'Entering directory src'
	thread_print`cd src; rake clean`
	thread_print'Leaving directory src'
	thread_print"  RM	bin/65db bin/fes test/*.nes"
	`rm bin/65db bin/fes test/*.nes`
end
