CC = g++
CFLAGS = -Wall -O3 --std=c++17

# Path to your existing random.h/cpp files
RANDOM_PATH = /home/elisa/Scrivania/LSN/LSN/Classes

# --- Add Conda environment prefix explicitly ---
# IMPORTANT: Replace this with the actual output of 'echo $CONDA_PREFIX'
# from your activated LSN environment.
CONDA_ENV_PREFIX = /home/elisa/miniconda3/envs/LSN

# Add Conda environment's include directory to CFLAGS
# This ensures g++ knows where to find <autodiff/forward/forward.hpp>
CFLAGS += -I$(CONDA_ENV_PREFIX)/include

# Specify the autodiff library name(s) to link against
# Based on your previous checks, these are likely correct if the .so/.a files exist.
LIBS = -larmadillo 

# -----------------------------------------------

main1.exe : main1.o random.o copy_files
    # The linker needs to know where the libraries are.
    # Conda usually sets LIBRARY_PATH, but explicit -L is safer if issues persist.
    # We can try without -L first, but if linking fails, add -L$(CONDA_ENV_PREFIX)/lib
	$(CC) main1.o random.o -o main1.exe $(LIBS)

main1.o : main1.cpp $(RANDOM_PATH)/random.h
    # This rule now uses the CFLAGS that include the Conda path,
    # plus your specific RANDOM_PATH include.
	$(CC) -c main1.cpp -o main1.o $(CFLAGS) -I$(RANDOM_PATH)

random.o : $(RANDOM_PATH)/random.cpp $(RANDOM_PATH)/random.h
	$(CC) -c $(RANDOM_PATH)/random.cpp -o random.o $(CFLAGS) -I$(RANDOM_PATH)

copy_files:
	cp $(RANDOM_PATH)/Primes .
	cp $(RANDOM_PATH)/seed.in .

clean :
	rm -f *.o main.exe Primes seed.in

