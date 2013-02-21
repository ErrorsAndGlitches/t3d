
.PHONY:all dox doxclean clean
OBJECT_DIR=obj
SOURCE_DIR=src
INCLUDE_DIR=include
VPATH=$(OBJECT_DIR):$(SOURCE_DIR):$(INCLUDE_DIR)

MAKE=g++
CXXFLAGS=-O2 -pipe -std=c++11 -I$(INCLUDE_DIR)
LDFLAGS=-lglut -lGLU -lGL -lSDL -lSDL_image

SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(notdir $(SOURCES:.cpp=.o))
EXECUTABLE=t3d

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	# ld flags should always be last!
	$(MAKE) $(CXXFLAGS) $(addprefix obj/, $(OBJECTS)) -o $@ $(LDFLAGS)

.cpp.o:
	$(MAKE) $(CXXFLAGS) $< -c -o $(OBJECT_DIR)/$(notdir $@)

dox: Doxyfile
	doxygen $^

doxclean:
	rm -rf html latex

clean:
	rm -rf $(OBJECT_DIR)/*.o $(EXECUTABLE)
