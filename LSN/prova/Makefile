CC = g++
CFLAGS = -Wall -O3 -std=c++17

# Path to your existing random.h/cpp files
RANDOM_PATH = ../Classes

# Include paths for our sources
CFLAGS += -I$(RANDOM_PATH) -I.

# Libraries
LIBS = -larmadillo

# -----------------------------------------------

main.exe: main.o random.o lib.o copy_files
	$(CC) main.o random.o lib.o -o main.exe $(LIBS)

main.o: main.cpp $(RANDOM_PATH)/random.h lib.h
	$(CC) -c main.cpp -o main.o $(CFLAGS)

random.o: $(RANDOM_PATH)/random.cpp $(RANDOM_PATH)/random.h
	$(CC) -c $(RANDOM_PATH)/random.cpp -o random.o $(CFLAGS)

lib.o: lib.cpp lib.h
	$(CC) -c lib.cpp -o lib.o $(CFLAGS)

copy_files:
	cp $(RANDOM_PATH)/Primes .
	cp $(RANDOM_PATH)/seed.in .

clean:
	rm -f *.o main1.exe Primes seed.in
