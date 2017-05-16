# Makefile

# Build the AGL library
release: physicalenvironment.cpp iphysicalobject.cpp movingobject.cpp ramp.cpp
	g++ -fPIC -c physicalenvironment.cpp
	g++ -fPIC -c iphysicalobject.cpp
	g++ -fPIC -c movingobject.cpp
	g++ -fPIC -c ramp.cpp
	g++ -shared -o ../lib/libagl-motion.so physicalenvironment.o iphysicalobject.o ramp.o movingobject.o -lSDL -lagl

# Build the AGL library for debugging
debug: physicalenvironment.cpp iphysicalobject.cpp movingobject.cpp ramp.cpp
	g++ -fPIC -g -c physicalenvironment.cpp
	g++ -fPIC -g -c iphysicalobject.cpp
	g++ -fPIC -g -c movingobject.cpp
	g++ -fPIC -g -c ramp.cpp
	g++ -shared -g -o ../lib/libagl-motion.so physicalenvironment.o iphysicalobject.o ramp.o movingobject.o -lSDL -lagl

# Build the test application
test: test.cpp
	g++ -g -o test test.cpp -lagl -lagl-motion


# Install the AGL library (debug) on the system
install_debug:
	../install_debug.sh

# Install the AGL library on the system
install:
	../install.sh

# Uninstall the AGL library to the system
remove:
	../remove.sh

# Generates the AGL documentation
doc:
	doxygen doxyfile

# Cleans the directories, removing executables and objects
clean:
	rm *.o test ../lib/*.so
