CC = g++
CFLAGS = -Wall -O3 --std=c++11
RANDOM_PATH = /home/elisa/Scrivania/LSN/LSN/Classes

main.exe : main.o random.o copy_files 
	$(CC) main.o random.o -o main.exe

main.o : main.cpp  $(RANDOM_PATH)/random.h 
	$(CC) -c main.cpp -o main.o $(CFLAGS) -I$(RANDOM_PATH)

random.o : $(RANDOM_PATH)/random.cpp $(RANDOM_PATH)/random.h
	$(CC) -c $(RANDOM_PATH)/random.cpp -o random.o $(CFLAGS) -I$(RANDOM_PATH)

copy_files:
	cp $(RANDOM_PATH)/Primes .
	cp $(RANDOM_PATH)/seed.in .

clean :
	rm -f *.o main.exe Primes seed.in