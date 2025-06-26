/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

#ifndef __System__
#define __System__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <armadillo>
#include <stdlib.h> //exit
#include "particle.h"
#include "random.h"

using namespace std;
using namespace arma;

class System { //data members hanno underscore

private:
  const int _ndim = 3;  // Dimensionality of the system
  bool _restart;        // Flag indicating if the simulation is restarted se= partiamo da zero, se =1 partiamo da vecchia simulazione
  bool _time_inversion;
  int _eq_steps;
  double _DeltaT;
  int _sim_type;        // Type of simulation (e.g., Lennard-Jones, Ising) (=0: dinamica molecolare)
  int _vdistr;          //type of initial velocity distribution (0:maxwell boltzmann, 1 dirac delta)
  int _npart;           // Number of particles
  int _nblocks;         // Number of blocks for block averaging
  int _nsteps;          // Number of simulation steps in each block
  int _nattempts;       // Number of attempted moves
  int _naccepted;       // Number of accepted moves
  double _temp, _beta;  // Temperature and inverse temperature
  double _rho, _volume; // Density and volume of the system
  double _r_cut;        // Cutoff radius for pair interactions -> taglio del potenziale sferico, <=r/2
  double _delta;        // Displacement step for particle moves (in din mol usato come Delta t)
  double _J, _H;        // Parameters for the Ising Hamiltonian: J spin totale, h campo magnetico este
  vec _side;            // Box dimensions
  vec _halfside;        // Half of box dimensions (contiene l/2 lungo le 3 direzioni)
  Random _rnd;          // Random number generator
  field <Particle> _particle; // Field of particle objects representing the system //FIELD=VETTORE DI PARTICELLE(classe di armadillo permette di codtruire vett, matrici tensori di altre classi)
  vec _fx, _fy, _fz;    // Forces on particles along x, y, and z directions

  // Properties
  int _nprop; // Number of properties being measured (all'inizio sono 5, ma dobbiamo aggiungerne una, che è un vettore -> diventano 5+ numero di bin dell'istogramma)
  bool _measure_penergy, _measure_kenergy, _measure_tenergy;// Flags for measuring different energies (misuro o no?)
  bool _measure_temp, _measure_pressure, _measure_gofr;     // Flags for measuring temperature, pressure, and radial dist. function
  bool _measure_magnet, _measure_cv, _measure_chi;          // Flags for measuring magnetization, heat capacity, and susceptibility
  bool _measure_pofv; 
//(ho un vettore di proprietà, perchè poi applico il data blocking a tutto il vettore-> lo faccio tutto in una volta)                                      // Flag for measuring the velocity modulus distribution
  int _index_penergy, _index_kenergy, _index_tenergy;       // Indices for accessing energy-related properties in vec _measurement 
  int _index_temp, _index_pressure, _index_gofr;            // Indices for accessing temperature, pressure, and radial dist. function
  int _index_magnet, _index_cv, _index_chi;                 // Indices for accessing magnetization, heat capacity, and susceptibility
  int _index_pofv;   
                                       // Index for accessing velocity modulus distribution
  int _n_bins;           // Number of bins for radial distribution function
  int _n_bins_v;         // Number of bins for velocity modulus distribution
  double _bin_size;      // Size of bins for radial distribution function
  double _bin_size_v;    // Size of bins for velocity modulus distribution
  double _vtail, _ptail; // Tail corrections for energy and pressure
//accumulatori delle osservabili
  vec _block_av;         // Block averages of properties
  vec _global_av;        // Global averages of properties
  vec _global_av2;       // Squared global averages of properties
  vec _average;          // Average values of properties (valor medio del blocco)
  vec _measurement;      // Measured values of properties (valori istantanei)


public: // Function declarations
  int get_nbl();              // Get the number of blocks
  int get_nsteps();           // Get the number of steps in each block
  int get_n_bins_v() {return _n_bins_v;};
  void initialize();          // Initialize system properties
  void initialize_properties();// Initialize properties for measurement
  void finalize();            // Finalize system and clean up
  void write_configuration(); // Write final system configuration to XYZ file
  void write_XYZ(int nconf);  // Write system configuration in XYZ format on the fly
  void read_configuration();  // Read system configuration from file
  void initialize_velocities();// Initialize particle velocities (serve per creare posizione al tempo t-delta t)
  void step();                // Perform a simulation step
  void block_reset(int blk);  // Reset block averages
  void measure();             // Measure properties of the system
  void averages(int blk);     // Compute averages of properties
  double error(double acc, double acc2, int blk); // Compute error
  void move(int part);        // Move a particle
  bool metro(int part);       // Perform Metropolis acceptance-rejection step
  double pbc(double position, int i); // Apply periodic boundary conditions for coordinates
  int pbc(int i);             // Apply periodic boundary conditions for spins
  void Verlet();              // Perform Verlet integration step
  double Force(int i, int dim); // Calculate force on a particle along a dimension
  double Boltzmann(int i, bool xnew); // Calculate Boltzmann factor for Metropolis acceptance

  void Get_Measurement(vec &meas);
  void time_inv();
  void Change_Temp(double T);
  void Set_Restart(double R);
void CheckSizes();
  void Set_Temp(double T);
    void Set_symtype(int ST);
    int Get_symtype();

    void equilibrate();


  double Get_Temp ();
  double GetRestart();
  void Reset_Averages();

void Change_nsteps(double Delta);

int Get_nsteps();

  void Set_h(double h);

};

#endif // __System__

/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
