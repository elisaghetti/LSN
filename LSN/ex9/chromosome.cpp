#include <cmath>
#include <cstdlib>
#include <string>
#include <armadillo>
#include "chromosome.h"

using namespace std;
using namespace arma;

void chromosome::set_element(int index,int val){
		cout<<"func"<<_chromosome.size()<<endl;
		_chromosome[index]=val;
	}
void chromosome::permutation(Random &rnd){
    
	int rand_index1,rand_index2;
	do{
	rand_index1 = int(rnd.Rannyu(1,_ngenes-1));
	rand_index2 = int(rnd.Rannyu(1,_ngenes-1));
	} while(rand_index1==rand_index2);
	int val = _chromosome[rand_index1];
	//do{ rand_value = int(rnd.Rannyu(1,chromosome.size()-1));}
	//while (rand_value==chromosome[rand_index]);
		_chromosome[rand_index1]=_chromosome[rand_index2];
		_chromosome[rand_index2]=val;

}

void chromosome::check_bonds(){
	if (_chromosome[0]!=0 or _chromosome[_ngenes+1]!=0) cerr<<"chromosome error: first and last city must have both index 0"<<endl;
	vec count_el = zeros(_ngenes);
	for (int i=0;i<_ngenes-1;i++){
		for (int j=0;j<_ngenes-1;j++){
			if(_chromosome[j]==i)count_el[i]++;
		}
	if (count_el[i]>1) cerr<<"chromosome error: city "<<i<<"is repeated "<<count_el[i]<<" times"<<endl;
	}

}