CC = g++
FLAGS = -std=c++11 -ggdb -Wall -O2
OBJ = matrix.o knn.o pca.o xval.o ppmloader/ppmloader.o file_helpers.o confusionM.o
EXECS = main tests

all: $(EXECS)

main: main.cpp $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $< -o $@

tests: tests.cpp $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $< -o $@

exp1: #Variando k del knn
	../tests/experimento1.sh

%.o: %.cpp %.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	-rm -f *.o
	-rm -f $(EXECS)
