require 'fileutils'

# Variables
# -----------------------------
AS65	=	'xa'
CC		=	'cc'
CFLAGS	=	'-Wfatal-errors'
LDFLAGS	=	'-lncurses'
OBJS	=	'65.o cpu.o ram.o rom.o disasm.o'


# Functions
# -----------------------------
# Remove file extension
def get_name(x)
	x.scan(/([\-a-z_0-9]+)\.(.*)/)[0][0]
end

# Remove file extension
def get_ext(x)
	x.scan(/([\-a-z_0-9]+)\.(.*)/)[0][1]
end

# Rule for .a65 to .nes
# like GNUMakefile .a65.nes: target
def a65_nes(x)

	# Get base filename
	y=get_name(x)

	# Run command if needed
	if !FileUtils.uptodate?('#{y}.nes',['#{y}.a65'])
		`set -x; #{AS65} #{y}.a65 -o #{y}.nes`
	else
		puts"nothing to be done for #{x}"
	end
end

# Rule for .c to .o
def c_o(x)

	# Get base filename
	y=get_name(x)

	# Run command if needed
	if !FileUtils.uptodate?('#{y}.o',['#{y}.c'])
		`set -x; #{CC} #{CFLAGS} #{LDFLAGS} -c #{y}.c`
	else
		puts"nothing to be done for #{x}"
	end
end

# Internal make method to allow
# multi-threaded builds
def thread_make(x)
	case get_ext(x)
		when 'o'
			c_o(x)
		when 'nes'
			a65_nes(x)
		else
			puts"No rule to make target \"#{x}\""
	end
end

# Generic make method to determine filetypes
# typeof y --> Array<String>
def make(x)
	threads=[]
	x.each do |y|
		threads.push(Thread.new{thread_make(y)})
	end
	threads.each do |z| z.join end
end

# Remove files
# typeof y is Array<String>
def clean(x)
	threads=[]
	x.each do |y|
		threads.push(Thread.new{`set -x; rm -f #{y}`})
	end
	threads.each do |z| z.join end
end


# Rules
# -----------------------------
task :default => [:_65, :test] do
	
end

task :_65 => [:objs] do
	`set -x; cc #{CFLAGS} #{LDFLAGS} #{OBJS} -o 65`
end

task :test do
	puts'Entering directory test'
	`cd test; set -x; rake`
	puts'Leaving directory test'
end

task :objs do
	make OBJS.split
end

task :clean do
	clean '65 nes.nes *.o'.split
end