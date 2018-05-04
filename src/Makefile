CC = g++
FLAGS = -std=c++11 -ggdb -Wall -O2
OBJ = matrix.o
EXECS = tests

all: $(EXECS)

main: tests.cpp $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $< -o $@


%.o: %.cpp %.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	-rm -f *.o
	-rm -f $(EXECS)
