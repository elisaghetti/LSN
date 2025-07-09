CC = g++
CFLAGS = -O3 --std=c++11
AFLAGS = -larmadillo
all: simulator.exe
simulator.exe : system.o ex4.o particle.o random.o
	$(CC) system.o particle.o random.o ex4.o -o simulator.exe $(AFLAGS)
ex7.o : ex7.cpp system.h particle.h color.h 
	$(CC) -c ex4.cpp -o ex4.o $(CFLAGS)
system.o : system.cpp system.h random.h particle.h color.h
	$(CC) -c system.cpp -o system.o $(CFLAGS)
particle.o : particle.cpp particle.h
	$(CC) -c particle.cpp -o particle.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o simulator.exe
remove:
	rm ../OUTPUT/*.*
	rm ../OUTPUT/CONFIG/*.*
