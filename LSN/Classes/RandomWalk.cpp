#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>

#include "RandomWalk.h"

using namespace std;

//CONSTRUCTORS
RandomWalk :: RandomWalk(){}
// Default constructor, does not perform any action

RandomWalk :: RandomWalk(int seed, int index){
	
	_rnd.RandomSetup(index);
}
RandomWalk :: RandomWalk(int N, double a){
	_Nsteps = N;
	_steplength=a;
}

RandomWalk :: RandomWalk(int seed, double a, double x, double y, double z){
    _rnd.RandomSetup(seed);
	_steplength=a;
	pos_x =x;
	pos_y=y;
	pos_z=z;
}

RandomWalk :: RandomWalk(double a, double x, double y, double z){
    _rnd.RandomSetup();
	_steplength=a;
	pos_x =x;
	pos_y=y;
	pos_z=z;
}

RandomWalk :: RandomWalk(Random rnd, vec start, double a){
	_rnd =rnd;
	//_rnd.RandomSetup();
	_steplength=a;
	_position = start;
}


RandomWalk :: ~RandomWalk(){}
// Default destructor, does not perform any action

void RandomWalk ::SetPosition(double x, double y, double z){
	pos_x =x;
	pos_y=y;
	pos_z=z;
}
void RandomWalk ::SetPosition(vec pos){
for (int i=0;i<3;i++) _position[i] = pos[i];
}



void RandomWalk ::Get_seed(){
	_rnd.SaveSeed();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RandomWalk::Step_3D (){

	double theta=_rnd.Rannyu(0,M_PI);
		double phi = _rnd.Rannyu(0,2*M_PI);

		double x= _steplength*sin(theta)*cos(phi);
		double y=_steplength*sin(theta)*sin(phi);
		double z= _steplength*cos(theta);

		pos_x += x;
		pos_y += y;
		pos_z += z;
}
/////////////////////////////////////////////////////////////////////////////////////////////////777
void RandomWalk::Step_Lattice (){
bool direction = true;
	 double a = _steplength;
	 //imposta il verso (avanti/indietro)
	double r1=_rnd.Rannyu();
	if (r1 <=0.5) direction = false;

	//imposta la direzione (x/y/z)
	double r2=_rnd.Rannyu();
	if(r2<= 1./3. ) {
		if (direction==true) pos_x += a;
		else pos_x += -a;
	}
	if(1./3. < r2 && r2<= 2./3.) {
				if (direction==true) pos_y += a;
				else pos_y+= -a;
	}

	if(2./3. <=r2) {
				if (direction==true) pos_z+= a;
				else pos_z += -a;
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RandomWalk::Step_unif (){

for (int i=0;i<3;i++){
	double step = _steplength*_rnd.Rannyu(-1.,1.);
 	_position[i] += step;
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*double RandomWalk :: GetDistance(){
	return sqrt(pos_x*pos_x + pos_y*pos_y + pos_z*pos_z);
}*/
double RandomWalk :: GetDistance(){
	return norm(_position);
}