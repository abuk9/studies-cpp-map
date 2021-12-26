headers = Map.h Employee.h
sources = TestMap.cpp
out = TestMap
flags = -Wall -pedantic

all: $(out)
	./$(out)

$(out): $(headers) $(sources)
	g++ -g $(flags) $(sources) -o $(out)

.PHONY: clean check debug

clean:
	-rm $(out)

check: $(out)
	valgrind ./$(out)

debug: $(out)
	gdb $(out)