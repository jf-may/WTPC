# These targets are not real files. Always execute them
.PHONY: default help objects executable all clean segfault dynamic static nobugs
# Defines the C compiler
CC = gcc 
# Flags to pass to the compiler
CFLAGS = 
# Defines the linker, defaulted to the compiler driver itself
LD = $(CC)

# Automatic source discovery
SOURCE_C = $(wildcard *.c)
# Object file name generation
OBJECTS_C = $(patsubst %.c, %_c.o, $(SOURCE_C))
# Executable file name generation
EXECUTABLES = $(patsubst %.c, %.e, $(SOURCE_C))

# Defines default target depending on all. make = make default = make all
default: all

# Defines make help
help:
	@echo "\
Options:\n\n\
  make all:           make every executable (default)\n\
  make segfault:      example with a segfault\n\
  make dynamic:       dynamic arrays with no segfault (doesn't mean no errors!)\n\
  make static:        static arrays, wrong result\n\
  make nobugs:        properly working\n\
  make clean:         delete output files\n\
  make help:          display this help"

objects: $(OBJECTS_C)

executable: $(EXECUTABLES)

all: objects executable

segfault: add_array_segfault.e 

dynamic: add_array_dynamic.e 

static: add_array_static.e 

nobugs: add_array_nobugs.e 

# Pattern rule for compilation
# Target(object): Dependencies(source)
%_c.o: %.c
# $^ = All dependencies
# -c = Compile only, do not link. Produces object file.
# $@ = Target name
	$(CC) $(CFLAGS) -c $^ -o $@

# Pattern rule for linking
%.e: %_c.o
	$(LD) $^ -o $@

clean:
	rm -rfv $(OBJECTS_C) $(EXECUTABLES)
