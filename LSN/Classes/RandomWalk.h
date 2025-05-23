#ifndef __RandomWalk__
#define __RandomWalk__

#include <vector>
#include <string>
#include "random.h"

class RandomWalk {

	protected:
		int N_steps;
		double step_length;

		double pos_x,pos_y,pos_z;

		Random rnd;

	public: //functions

	  // Default constructorS
		RandomWalk();
		RandomWalk(int seed,int index);
		RandomWalk(int N, double a);
		RandomWalk(int N, double a, double x, double y, double z);
		RandomWalk(double a, double x, double y, double z);
	  // Destructor
		~RandomWalk();

		void Get_seed ();

		void SetNSteps(int N) {N_steps = N;}
		int GetNSteps(){return N_steps;}

		double Get_x () {return pos_x;};
		double Get_y () {return pos_y;};
		double Get_z () {return pos_z;};

		double GetDistance();

		void SetPosition(double x, double y, double z);

		void Set_Seed(int index);


		void Step_3D ();
		void Step_Lattice ();
		//one step of a continuum RW in 3D

		//void Step_3D (std::vector <double> pos_x, std::vector <double> pos_y, std::vector <double> pos_z, std::string file);



};



#endif