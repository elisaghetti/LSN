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

RandomWalk :: RandomWalk(int seed, int dim,int N, double a){
	
	_rnd.RandomSetup(seed);
	_position=zeros(dim);
	_Nsteps = N;
	_steplength=a;
}

RandomWalk :: RandomWalk(int seed, int N, double a,vec start_pos){
	_rnd.RandomSetup(seed);
	_position=start_pos;
	_Nsteps = N;
	_steplength=a;

}
RandomWalk :: RandomWalk(Random rnd,vec start_pos,double a){
	_rnd = rnd;
	_position=start_pos;
	_steplength=a;

}



RandomWalk :: ~RandomWalk(){}

void RandomWalk ::SetPosition(double x, double y, double z){
	_position[0] =x;
	_position[1]=y;
	_position[2]=z;
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

		_position[0]  += x;
		_position[1]  += y;
		_position[2]  += z;


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
		if (direction==true) _position[0]  += a;
		else _position[0]  += -a;
	}
	if(1./3. < r2 && r2<= 2./3.) {
				if (direction==true) _position[1] += a;
				else _position[1] += -a;
	}

	if(2./3. <=r2) {
				if (direction==true) _position[2] += a;
				else _position[2]  += -a;
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RandomWalk::Step_unif (){

for (int i=0;i<3;i++){
	double step = _steplength*_rnd.Rannyu(-1.,1.);
 	_position[i] += step;
}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void RandomWalk::Step_gauss (){

for (int i=0;i<3;i++){
	double step = _rnd.Gauss(0.,_steplength);
 	_position[i] += step;
}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*double RandomWalk :: GetDistance(){
	return sqrt(pos_x*pos_x + pos_y*pos_y + pos_z*pos_z);
}*/
double RandomWalk::GetDistance(){
	return norm(_position);
}