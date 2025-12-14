#ifndef __RandomWalk__
#define __RandomWalk__

#include <vector>
#include <string>
#include "random.h"
#include <armadillo>

using namespace std;
using namespace arma;

class RandomWalk {

	protected:
		int _Nsteps;
		double _steplength;
		vec _position;
		int _dim;
	

		Random _rnd;

	public: //functions

	  // Default constructorS
		RandomWalk();
		RandomWalk(int seed,int index,int N, double a);
	
	
		RandomWalk(int seed, int N, double a,vec start_pos);
	  // Destructor
		~RandomWalk();

		void Get_seed ();

		void SetNSteps(int N) {_Nsteps = N;}
		int GetNSteps(){return _Nsteps;}

		double Get_x () {return _position[0];};
		double Get_y () {return _position[1];};
		double Get_z () {return _position[2];};

		vec Get_position(){return _position;};

		double GetDistance();

		void SetPosition(double x, double y, double z);
		void SetPosition(vec pos);
		void Set_Seed(int index);


		void Step_3D ();//random direction,fixed step length
		void Step_Lattice ();//fixed step length on fixed axis
		void Step_unif(); //random direction, random step length
		void Step_gauss(); //random direction, random step length
		

		//void Step_3D (std::vector <double> pos_x, std::vector <double> pos_y, std::vector <double> pos_z, std::string file);



};



#endif