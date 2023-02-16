.PHONY: all, clean, rebuild

CC = g++ -std=c++20
CFLAGS = -c

SOURCES =  $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = MAIN.out


all: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)
	./$(EXECUTABLE)

re: rebuild

rebuild: clean all

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -rf  *.o *.out