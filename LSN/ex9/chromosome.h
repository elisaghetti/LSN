#ifndef __chromosome__
#define __chromosome__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <armadillo>
#include <stdlib.h> 
#include <random.h>

using namespace std;
using namespace arma;

class chromosome { 

    private: 

    int _ngenes;
    vec _chromosome;
	vec _position;
	int _simtype;

    public:

		chromosome (){};
  // Destructor
        ~chromosome(){};
	

   void initialize(int n,int sim_type) {
        _ngenes=n;
		cout<<_ngenes<<endl;
		_simtype=sim_type;
        _chromosome = zeros(_ngenes+1);
		cout<<"init"<<_chromosome.size()<<endl;
		//if (_simtype==0) _positions=zeros(2,_ngenes); //cerchio: matrice 2xN
		//if (_simtype==1) _positions=zeros(3,_ngenes);
	};
	/*
	void assign_positions(){
		if (_simtype ==0){
			cout<<"Simulating "<<_ngenes<<" on a circle";
			double dtheta = 2*M_PI/(double(_ngenes));
			double theta =0.;
			for (int i=0;i<_ngenes;i++){
				double x =cos(theta);
				double y=sin(theta);
				theta += dtheta;
			_positions(0,i) = x;
			_positions(1,i)= y;
			}
		}
	}
*/
	void set_element(int index,int val);
	inline vec get_vector (){
		return _chromosome;
	}
    void permutation(Random &rnd);
    void check_bonds();
	 };

#endif