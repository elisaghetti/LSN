#include <cmath>
#include <cstdlib>
#include <string>
#include <armadillo>
#include "chromosome.h"

using namespace std;
using namespace arma;

void chromosome::set_element(int index,gene val){

		_chromosome(index)=val;
	}

void chromosome::assign_positions(){
		if (_simtype ==0){
	
			double dtheta = 2*M_PI/(double(_ngenes));
			double theta =0.;
			for (int i=0;i<_ngenes;i++){
				vec pos = zeros(2);
				pos[0] =cos(theta);
				pos[1]=sin(theta);
				theta += dtheta;
				_chromosome(i).position = pos;

			}
			_chromosome(_ngenes).position = _chromosome(0).position;
		}
	}

void chromosome::permutation(Random &rnd){
    
	int rand_index1,rand_index2;
	do{
	rand_index1 = int(rnd.Rannyu(1,_ngenes));
	rand_index2 = int(rnd.Rannyu(1,_ngenes));
	} while(rand_index1==rand_index2);
	gene val = _chromosome(rand_index1);

		_chromosome(rand_index1)=_chromosome(rand_index2);
		_chromosome(rand_index2)=val;

}

void chromosome::check_bonds(){
	if (_chromosome(0).index!=0 or _chromosome(_ngenes).index!=0) cerr<<"chromosome error: first and last city must have both index 0"<<endl;
	vec count_el = zeros(_ngenes);
	for (int i=0;i<_ngenes-1;i++){
		for (int j=0;j<_ngenes-1;j++){
			if(_chromosome(j).index==i)count_el[i]++;
		}
	if (count_el[i]>1) cerr<<"chromosome error: city "<<i<<"is repeated "<<count_el[i]<<" times"<<endl;
	}
	if(_chromosome(0).position[0]!= _chromosome(_ngenes).position[0] or _chromosome(0).position[1]!= _chromosome(_ngenes).position[1])cerr<<"First and last positions must be fixed and the same"<<endl;


}

double chromosome::get_distance(int i1,int i2){
	vec delta = _chromosome(i1).position -_chromosome(i2).position;
	return norm(delta);

}

void chromosome::compute_fitness(){
	double L1=0.;
	for (int i=0; i<_ngenes;i++){
		L1+= get_distance(i,i+1);
	}
	_fitness=L1;
}
void chromosome::print_configuration(){
	for (int i=0;i<_ngenes+1;i++){
		cout<<_chromosome(i).index;
	}
	cout<<endl;
}

vec chromosome::get_indices_vector(){
	vec indices = zeros(_ngenes+1);
	for (int i=0;i<_ngenes+1;i++)indices(i)=_chromosome(i).index;

return indices;
}
//MUTATIONS///////////////////////////

void chromosome::shift_cities(Random &rnd){
	int c1 = int (rnd.Rannyu(1,_ngenes-1));
	cout<<c1<<"\t";//prima città del blocco da spostare
	int c2 = int (rnd.Rannyu(c1,_ngenes-1));
	cout<<c2<<"\t"; //ultima cttà del blocco
	int Nshifted = c2-c1+1;

	int shift_length = int(rnd.Rannyu(0,_ngenes-1-c2));
	cout<<shift_length<<endl;
	
	//work on indices vector
	vec cities = get_indices_vector();
	vec block = cities.subvector(c1,c2);
	vec before = cities.subvector(0,c1-1);
	vec after = cities.subvector(c2+1,_ngenes);
	
	if(before.size()>0&& after.size()>0)vec tmp = join_vert(before,after);
	else if (before.size()>0) vec tmp = before;
	else  vec tmp=after;

	int newpos= c1+shift_length;
	vec newbefore = (newpos>0)?tmp.subvec(0,newpos-1) : vec();
	vec newafter= (newpos<tmp.n_elem)? tmp.subvec(newpos,tmp.n_elem-1);
	vec result;
	if(newbefore.n_elem>0)result= newbefore;
	if(block.nelem>0) result = (result.nelem >0)

	

}
