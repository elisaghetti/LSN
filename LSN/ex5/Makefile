CC = g++
CFLAGS = -Wall -O3 --std=c++11
RANDOM_PATH = /home/elisa/Scrivania/LSN/LSN/Classes

main.exe : main.o random.o statistics.o RandomWalk.o copy_files 
	$(CC) main.o random.o statistics.o RandomWalk.o -o main.exe -larmadillo

main.o : main.cpp $(RANDOM_PATH)/statistics.h $(RANDOM_PATH)/RandomWalk.h $(RANDOM_PATH)/random.h 
	$(CC) -c main.cpp -o main.o $(CFLAGS) -I$(RANDOM_PATH)

statistics.o : $(RANDOM_PATH)/statistics.cpp $(RANDOM_PATH)/statistics.h  $(RANDOM_PATH)/random.h 
	$(CC) -c $(RANDOM_PATH)/statistics.cpp -o statistics.o $(CFLAGS) -I$(RANDOM_PATH)

RandomWalk.o : $(RANDOM_PATH)/RandomWalk.cpp $(RANDOM_PATH)/RandomWalk.h  $(RANDOM_PATH)/random.h 
	$(CC) -c $(RANDOM_PATH)/RandomWalk.cpp -o RandomWalk.o $(CFLAGS) -I$(RANDOM_PATH)

random.o : $(RANDOM_PATH)/random.cpp $(RANDOM_PATH)/random.h
	$(CC) -c $(RANDOM_PATH)/random.cpp -o random.o $(CFLAGS) -I$(RANDOM_PATH)

copy_files:
	cp $(RANDOM_PATH)/Primes .
	cp $(RANDOM_PATH)/seed.in .

clean :
	rm -f *.o main.exe Primes seed.in