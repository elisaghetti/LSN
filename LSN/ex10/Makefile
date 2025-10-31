CC = mpic++
CFLAGS = -O3 --std=c++11
# Path to your existing random.h/cpp files
CLASSES_PATH = ../Classes

# Include paths for our sources
CFLAGS += -I$(CLASSES_PATH) -I.
all: main.exe
main.exe : parallel_GeneticOptimizer.o main.o parallel_chromosome.o random.o continent.o copy_files
	$(CC) parallel_GeneticOptimizer.o parallel_chromosome.o main.o random.o continent.o -o main.exe 
main.o : main.cpp $(CLASSES_PATH)/parallel_GeneticOptimizer.h $(CLASSES_PATH)/parallel_chromosome.h continent.h
	$(CC) -c main.cpp -o main.o $(CFLAGS)
random.o: $(CLASSES_PATH)/random.cpp $(CLASSES_PATH)/random.h
	$(CC) -c $(CLASSES_PATH)/random.cpp -o random.o $(CFLAGS)
parallel_GeneticOptimizer.o : $(CLASSES_PATH)/parallel_GeneticOptimizer.cpp $(CLASSES_PATH)/parallel_GeneticOptimizer.h $(CLASSES_PATH)/parallel_chromosome.h
	$(CC) -c $(CLASSES_PATH)/parallel_GeneticOptimizer.cpp -o parallel_GeneticOptimizer.o $(CFLAGS)
parallel_chromosome.o : $(CLASSES_PATH)/parallel_chromosome.cpp $(CLASSES_PATH)/parallel_chromosome.h 
	$(CC) -c $(CLASSES_PATH)/parallel_chromosome.cpp -o parallel_chromosome.o $(CFLAGS)
continent.o : continent.cpp continent.h $(CLASSES_PATH)/parallel_chromosome.h $(CLASSES_PATH)/parallel_GeneticOptimizer.h
	$(CC) -c continent.cpp -o continent.o $(CFLAGS)

copy_files:
	cp $(CLASSES_PATH)/Primes .
	cp $(CLASSES_PATH)/seed.in .

clean:
	rm -f *.o main.exe Primes seed.in
