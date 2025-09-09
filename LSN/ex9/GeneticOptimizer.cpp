#include <cmath>
#include <cstdlib>
#include <string>
#include <armadillo>
#include "GeneticOptimizer.h"
#include "chromosome.h"

using namespace std;
using namespace arma;



void GeneticOptimizer::create_starting_population(Random &rnd){
  chromosome ch;

		ch.initialize(_Ngenes,_simtype);
		ch.assign_positions(rnd);
		ch.compute_fitness();
		//_fitness_values.push_back(ch.get_fitness());

		for (int i=0; i<_population_size;i++){
		int n_perm = int(rnd.Rannyu(1,_Ngenes));//number of permutations
		
		chromosome new_ch = ch;
		for(int j=0;j<n_perm;j++) new_ch.permutation(rnd);
		new_ch.compute_fitness();
		_population.push_back(new_ch);
		new_ch.check_bonds();
		
		_fitness_values.push_back(new_ch.get_fitness());
	
	}


	}

	void GeneticOptimizer::print_configuration(){
		ofstream out("./OUTPUT/positions.csv");
	out<<"ch_index\tindex\tx\ty"<<endl;
	for (int i=0; i<_population_size;i++){
		for (int j=0; j<_Ngenes+1;j++){
			out<<i<<"\t"<<_population[i].get_gene(j).index<<"\t"<<_population[i].get_gene(j).position[0]<<"\t"<<_population[i].get_gene(j).position[1]<<endl;
		}

	}
	out.close();
}

void GeneticOptimizer::sort_population(){
	

	sort (_population.begin(),_population.end(), [](chromosome a, chromosome b) {
              return a.get_fitness() > b.get_fitness();
          });

	   for (int i = 0; i < _population_size; i++) {
        _fitness_values[i]=_population[i].get_fitness();
    }

	
		
}

void GeneticOptimizer::check_order(){
	vec fitness_values = zeros(_population_size);
	for (int i=0;i<_population_size;i++){
		_population[i].compute_fitness();
		fitness_values[i]= _population[i].get_fitness();

	}

	if (fitness_values.is_sorted("descend")) cout<<"population sorted succesfully"<<endl;
	else cerr<<"sorting error"<<endl;

}

int GeneticOptimizer::selection(Random &rnd){
	bool accept = false;
	int result =0;
	while(accept==false){
	
	int cand = int(rnd.Rannyu(0,_population_size));
	/*
	double norm = *max_element(_fitness_values.begin(),_fitness_values.end());
	double normalized_fitness=_population[cand].get_fitness()/norm;
	*/
	double r = rnd.Exp(0.75);
	
	//double r = rnd.Rannyu()
	if (r>=cand/double(_population_size)) {
		result = cand;
		accept = true;
	}
	}
	return result;
}

void GeneticOptimizer::select_parents(Random &rnd){
	ofstream out("./OUTPUT/selection.csv");
	out<<"gen\tselected"<<endl;
	int p1,p2;
	for (int i = 0; i<5000; i++){
	
	int p1 = selection(rnd);
	//int p2 = selection (rnd);

	out<<i<<"\t"<<p1<<endl;
	//out<<p2<<endl;
	}
	out.close();
}

void GeneticOptimizer::random_search (Random &rnd, int ngen){
	ofstream out("./OUTPUT/random_search.csv");
	out<<"gen\tresults"<<endl;
	for (int i=0;i<ngen;i++){
		for (chromosome x:_population) {
			x.mutation(rnd);
			x.check_bonds();
		}
		sort_population();
		
		int result = selection(rnd);
		
		out<<i<<"\t"<<result<<endl;
	}
	out.close();
}

void GeneticOptimizer::crossover_g(Random &rnd, int p1, int p2){
	double p_cross = rnd.Rannyu();
	//if(p_cross<=0.5){
	chromosome genitore1 = _population[p1];
	chromosome genitore2 = _population[p2];
		//int cut_pos =int(rnd.Rannyu(1,_Ngenes));
		int cut_pos = 7;
		cout<<cut_pos<<endl;
	genitore1.print_configuration();
	genitore2.print_configuration();
	_population[p1].crossover(cut_pos,genitore2);
	_population[p2].crossover(cut_pos,genitore1);
	_population[p1].print_configuration();
	_population[p2].print_configuration();

	//bool check1,check2;
/*
	vector <gene> genitore1 = _population[p1].get_genevector();
	_population[p1].print_configuration();
	vector <gene> genitore2 = _population[p2].get_genevector();
	_population[p2].print_configuration();

	
	vector <gene> gen1_block (genitore1.begin()+start,genitore1.end()-1);
	vector <gene> ordered_block;
	for (gene x:genitore2){
		for (gene y : gen1_block){
			if (x.get_index()==y.get_index()) ordered_block.append(y);
		}
	}
	genitore1.cut(cut_pos);
	genitore1.paste(ordered_block);
	//cout<<"cut"<<endl;
		vector <gene> gen2_block (genitore2.begin()+start,genitore2.end()-1);
	vector <gene> ordered_block2;
	for (gene x:_population[p1].get_genevector()){
		for (gene y : gen2_block){
			if (x.get_index()==y.get_index()) ordered_block2.append(y);
		}
	}
	genitore2.cut(cut_pos);
	genitore2.paste(ordered_block2);

	//check1=genitore1.check_bonds1();
	//check2=genitore2.check_bonds1();
	_population[p1].set_genevector(genitore1);
	_population[p2].set_genevector(genitore2);
	_population[p1].print_configuration();
_population[p2].print_configuration();
	_population[p1].check_bonds();
	_population[p2].check_bonds();
	//}while(check1==false or check2==false);
//	}
	*/


}

chromosome GeneticOptimizer::optimize (Random &rnd, int ngen){
	for (int i=0;i<ngen;i++){
		sort_population();

		for (int i=0; i<_population_size;i++){
		double r =rnd.Rannyu();
		if(r<0.7){
		int p2=selection(rnd);
	
		chromosome genitore1 = _population[i];
		chromosome genitore2 = _population[p2];
		int cut_pos =int(rnd.Rannyu(1,_Ngenes));

	_population[i].crossover(cut_pos,genitore2);
	_population[p2].crossover(cut_pos,genitore1);

		//crossover()

		_population[i].mutation(rnd);
		_population[p2].mutation(rnd);
		}
	//}
	}
}
	sort_population();
	//for (double f : _fitness_values) cout<<f<<" ";
	//cout<<endl;
//return _population[_population_size-1];
return _population[0];
}