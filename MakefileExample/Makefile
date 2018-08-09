#This is a comment

#Compiler to use
CC=gcc
#Flags, for example to specify include directories
CFLAGS=-I.
#Dependencies, like header files
DEPS = include/%.h
#Object files to build and link to obtain target executable
OBJ = add.o
#Name of target executable
TARGET = add

#Creates object files
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# The first "target" listed below is the default that gets built
# if nothing else is specified.

#Links object files to create executable
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Declare "PHONY" targets: these don't build anything
.PHONY: clean test

#Cleans all compilation output files
clean:
	rm -f *.o *~ $(TARGET) output

#Test-runs the executable
test: $(TARGET)
	./$(TARGET) < input > output
	diff output golden_output

archive: clean
	@tar -czf ../dsa-submit.tgz -C .. `basename ${PWD}`
	@echo "Created the archive file ../dsa-submit.tgz.  Please submit to Moodle."
