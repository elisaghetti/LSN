#include <cmath>
#include <cstdlib>
#include <string>
#include <armadillo>
#include "GeneticOptimizer.h"
#include "chromosome.h"

using namespace std;
using namespace arma;
/*
void GeneticOptimizer::assign_positions(Random &rnd,int sim_type,int index,chromosome &ch){
			if (_simtype ==0){
			cout<<"Simulating "<<_ngenes<<" on a circle";
			double dtheta = 2*M_PI/(double(_Ngenes));
			double theta =dtheta*index.;
			for (int i=0;i<_ngenes;i++){
				double x =cos(theta);
				double y=sin(theta);
				theta += dtheta;
				chromosome ch= _population.col(i);
				ch.assign_position()
			_positions(0,i) = x;
			_positions(1,i)= y;
			}
		}
}
void GeneticOptimizer::create_starting_population(Random &rnd,int sim_type){
  chromosome ch;
  cout<<_Ngenes<<endl;
		ch.initialize(_Ngenes,sim_type);
    
		for (int i=1;i<_Ngenes;i++) ch.set_element(i,i);

    cout<<"chekc"<<endl;
   cout<<ch.get_vector()<<endl;
		for (int i=0; i<_population_size;i++){
		int n_perm = int(rnd.Rannyu(0,_Ngenes+1));//number of permutations
		//cout<<n_perm;
		chromosome new_ch = ch;
		for(int j=0;j<n_perm;j++) new_ch.permutation(rnd);
		_population.col(i)=new_ch.get_vector();
		new_ch.check_bonds();
		
	}
	cout<<_population<<endl;

	}*/