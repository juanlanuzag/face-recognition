CC = g++
FLAGS = -std=c++11 -ggdb -Wall -O2
OBJ = matrix.o knn.o helpers.o xval.o ppmloader/ppmloader.o
EXECS = main tests

all: $(EXECS)

main: main.cpp $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $< -o $@

tests: tests.cpp $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $< -o $@


%.o: %.cpp %.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	-rm -f *.o
	-rm -f $(EXECS)
