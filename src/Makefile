CC = g++
FLAGS = -std=c++11 -ggdb -Wall -O2
OBJ = matrix.o knn.o pca.o xval.o ppmloader/ppmloader.o file_helpers.o confusionM.o
EXECS = main experimentotiempos

all: $(EXECS)

main: main.cpp $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $< -o $@

experimentotiempos: experimentotiempos.cpp $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $< -o $@

%.o: %.cpp %.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	-rm -f *.o
	-rm -f $(EXECS)
