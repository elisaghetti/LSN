CC = g++
CFLAGS = -O3 --std=c++11
# Path to your existing random.h/cpp files
RANDOM_PATH = ../Classes

# Include paths for our sources
CFLAGS += -I$(RANDOM_PATH) -I.
AFLAGS = -larmadillo
all: main.exe
main.exe : GeneticOptimizer.o main.o chromosome.o random.o copy_files
	$(CC) GeneticOptimizer.o chromosome.o main.o random.o -o main.exe $(AFLAGS)
main.o : main.cpp GeneticOptimizer.h chromosome.h
	$(CC) -c main.cpp -o main.o $(CFLAGS)
random.o: $(RANDOM_PATH)/random.cpp $(RANDOM_PATH)/random.h
	$(CC) -c $(RANDOM_PATH)/random.cpp -o random.o $(CFLAGS)
GeneticOptimizer.o : GeneticOptimizer.cpp GeneticOptimizer.h chromosome.h
	$(CC) -c GeneticOptimizer.cpp -o GeneticOptimizer.o $(CFLAGS)
chromosome.o : chromosome.cpp chromosome.h
	$(CC) -c chromosome.cpp -o chromosome.o $(CFLAGS)

copy_files:
	cp $(RANDOM_PATH)/Primes .
	cp $(RANDOM_PATH)/seed.in .

clean:
	rm -f *.o main.exe Primes seed.in
