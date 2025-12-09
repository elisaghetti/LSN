CC = g++
CFLAGS = -Wall -O3 --std=c++11
RANDOM_PATH = /home/elisa/Scrivania/LSN/LSN/Classes

main1.exe : main1.o random.o copy_files 
	$(CC) main1.o random.o -o main1.exe

main2.exe : main2.o random.o copy_files 
	$(CC) main2.o random.o -o main2.exe

main3.exe : main3.o random.o copy_files 
	$(CC) main3.o random.o -o main3.exe

main1.o : main1.cpp  $(RANDOM_PATH)/random.h 
	$(CC) -c main1.cpp -o main1.o $(CFLAGS) -I$(RANDOM_PATH)

main2.o : main2.cpp  $(RANDOM_PATH)/random.h 
	$(CC) -c main2.cpp -o main2.o $(CFLAGS) -I$(RANDOM_PATH)

main3.o : main3.cpp  $(RANDOM_PATH)/random.h 
	$(CC) -c main3.cpp -o main3.o $(CFLAGS) -I$(RANDOM_PATH)

random.o : $(RANDOM_PATH)/random.cpp $(RANDOM_PATH)/random.h
	$(CC) -c $(RANDOM_PATH)/random.cpp -o random.o $(CFLAGS) -I$(RANDOM_PATH)

copy_files:
	cp $(RANDOM_PATH)/Primes .
	cp $(RANDOM_PATH)/seed.in .

clean :
	rm -f *.o main1.exe main2.exe main3.exe seed.out Primes seed.in