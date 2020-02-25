# Basic Rakefile functionality include file

# Functions
# -----------------------------
# Remove file extension
def thread_print(x)
	$stdout_mutex.synchronize do
		puts x
	end
end

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
		#`set -x; #{$AS65} #{y}.a65 -o #{y}.nes`

		thread_print"AS65 #{y}.nes"
		`#{$AS65} #{y}.a65 -o #{y}.nes`
	else
		thread_print"nothing to be done for #{x}"
	end
end

# Rule for .c to .o
def c_o(x)

	# Get base filename
	y=get_name(x)

	# Run command if needed
	if !FileUtils.uptodate?('#{y}.o',['#{y}.c'])
		#`set -x; #{$CC} #{$CFLAGS} #{$LDFLAGS} -c #{y}.c`

		thread_print"CC\t#{y}.o"
		`#{$CC} #{$CFLAGS} #{$LDFLAGS} -c #{y}.c`
	else
		thread_print"nothing to be done for #{x}"
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
			thread_print"No rule to make target \"#{x}\""
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
		#threads.push(Thread.new{`set -x; rm -f #{y}`})

		thread_print"RM\t#{y}"
		threads.push(Thread.new{`rm -f #{y}`})
	end
	threads.each do |z| z.join end
end
