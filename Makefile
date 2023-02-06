SOURCES = $(shell find . -type f -name '*.cpp')
HEADERS = $(shell find . -type f -name '*.hpp')
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean



all: $(OBJECTS) $(HEADERS)
	g++ $^ -o xml-reader -O2

clean:
	rm -rf $(OBJECTS)
	rm -f out

%.o: %.cpp 
	g++ -c $< -o $@ -O2