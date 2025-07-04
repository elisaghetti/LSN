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
		double pos_x,pos_y,pos_z;

		Random _rnd;

	public: //functions

	  // Default constructorS
		RandomWalk();
		RandomWalk(int seed,int index);
		RandomWalk(int N, double a);
		RandomWalk(int seed, double a, double x, double y, double z);
		RandomWalk(double a, double x, double y, double z);
		RandomWalk(Random rnd, vec start, double a);
	  // Destructor
		~RandomWalk();

		void Get_seed ();

		void SetNSteps(int N) {_Nsteps = N;}
		int GetNSteps(){return _Nsteps;}

		double Get_x () {return pos_x;};
		double Get_y () {return pos_y;};
		double Get_z () {return pos_z;};

		vec Get_position(){return _position;};

		double GetDistance();

		void SetPosition(double x, double y, double z);
		void SetPosition(vec pos);
		void Set_Seed(int index);


		void Step_3D ();//random direction,fixed step length
		void Step_Lattice ();//fixed step length on fixed axis
		void Step_unif(); //random direction, random step length
		

		//void Step_3D (std::vector <double> pos_x, std::vector <double> pos_y, std::vector <double> pos_z, std::string file);



};



#endif