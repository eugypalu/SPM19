OBJECTS = main.cpp
CFLAGS = -pthread -std=c++17 
CC = g++
PROGRAM_NAME = main.o
OMP = main_OMP.cpp

$(PROGRAM_NAME):$(OBJECTS)
	$(CC) $(CFLAGS) -o $(PROGRAM_NAME) $(OBJECTS)


omp:
	$(CC) $(CFLAGS) -fopenmp -o omp.o $(OMP) 

clean: 
	rm -f *.o
	@echo "Clean done"
