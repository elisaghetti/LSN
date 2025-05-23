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
	
	rnd.RandomSetup(index);
}
RandomWalk :: RandomWalk(int N, double a){
	N_steps = N;
	step_length=a;
}

RandomWalk :: RandomWalk(int seed, double a, double x, double y, double z){
    rnd.RandomSetup(seed);
	step_length=a;
	pos_x =x;
	pos_y=y;
	pos_z=z;
}

RandomWalk :: RandomWalk(double a, double x, double y, double z){
	rnd.RandomSetup();
	step_length=a;
	pos_x =x;
	pos_y=y;
	pos_z=z;
}


RandomWalk :: ~RandomWalk(){}
// Default destructor, does not perform any action

void RandomWalk ::SetPosition(double x, double y, double z){
	pos_x =x;
	pos_y=y;
	pos_z=z;
}



void RandomWalk ::Get_seed(){
	rnd.SaveSeed();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RandomWalk::Step_3D (){

	double theta=rnd.Rannyu(0,M_PI);
		double phi = rnd.Rannyu(0,2*M_PI);

		double x= step_length*sin(theta)*cos(phi);
		double y=step_length*sin(theta)*sin(phi);
		double z= step_length*cos(theta);

		pos_x += x;
		pos_y += y;
		pos_z += z;
}
/////////////////////////////////////////////////////////////////////////////////////////////////777
void RandomWalk::Step_Lattice (){
bool direction = true;
	 double a = step_length;
	 //imposta il verso (avanti/indietro)
	double r1=rnd.Rannyu();
	if (r1 <=0.5) direction = false;

	//imposta la direzione (x/y/z)
	double r2=rnd.Rannyu();
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
/*void RandomWalk::Step_3D (double pos_x, double pos_y, double pos_z){
	double theta=Rannyu(0,M_PI);
		double phi = Rannyu(0,2*M_PI);

		double x= step_length*sin(theta)*cos(phi);
		double y=step_length*sin(theta)*sin(phi);
		double z= step_length*cos(theta);

		pos_x += x;
		pos_y += y;
		pos_z += z;
}
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double RandomWalk :: GetDistance(){
	return sqrt(pos_x*pos_x + pos_y*pos_y + pos_z*pos_z);
}