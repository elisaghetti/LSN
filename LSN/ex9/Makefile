CC = g++
CFLAGS = -O3 --std=c++11
AFLAGS = -larmadillo
all: main.exe
main.exe : GeneticOptimizer.o main.o chromosome.o 
	$(CC) GeneticOptimizer.o chromosome.o main.o -o main.exe $(AFLAGS)
main.o : main.cpp GeneticOptimizer.h chromosome.h
	$(CC) -c main.cpp -o main.o $(CFLAGS)
GeneticOptimizer.o : GeneticOptimizer.cpp GeneticOptimizer.h chromosome.h
	$(CC) -c GeneticOptimizer.cpp -o GeneticOptimizer.o $(CFLAGS)
chromosome.o : chromosome.cpp chromosome.h
	$(CC) -c chromosome.cpp -o chromosome.o $(CFLAGS)

clean :
	rm *.o main.exe
