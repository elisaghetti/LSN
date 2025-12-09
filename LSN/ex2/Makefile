CC = g++
CFLAGS = -Wall -O3 --std=c++11
RANDOM_PATH = /home/elisa/Scrivania/LSN/LSN/Classes

main1.exe : main1.o random.o  copy_files 
	$(CC) main1.o random.o  -o main1.exe

main2.exe : main2.o random.o  RandomWalk.o copy_files 
	$(CC) main2.o random.o RandomWalk.o -o main2.exe -larmadillo

main1.o : main1.cpp  $(RANDOM_PATH)/random.h 
	$(CC) -c main1.cpp -o main1.o $(CFLAGS) -I$(RANDOM_PATH)

main2.o : main2.cpp  $(RANDOM_PATH)/RandomWalk.h $(RANDOM_PATH)/random.h 
	$(CC) -c main2.cpp -o main2.o $(CFLAGS) -I$(RANDOM_PATH)

random.o : $(RANDOM_PATH)/random.cpp $(RANDOM_PATH)/random.h
	$(CC) -c $(RANDOM_PATH)/random.cpp -o random.o $(CFLAGS) -I$(RANDOM_PATH)

RandomWalk.o : $(RANDOM_PATH)/RandomWalk.cpp $(RANDOM_PATH)/RandomWalk.h  $(RANDOM_PATH)/random.h 
	$(CC) -c $(RANDOM_PATH)/RandomWalk.cpp -o RandomWalk.o $(CFLAGS) -I$(RANDOM_PATH)

copy_files:
	cp $(RANDOM_PATH)/Primes .
	cp $(RANDOM_PATH)/seed.in .

clean :
	rm -f *.o main1.exe main2.exe seed.out Primes seed.in