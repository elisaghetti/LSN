#include <cmath>
#include <cstdlib>
#include <string>

#include "parallel_chromosome.h"
#include "mpi.h"

using namespace std;


vector <double> parallel_chromosome::get_position(int i){
			vector <double> pos;
			pos.push_back(_chromosome[i].x);
			pos.push_back(_chromosome[i].y);
		return pos;
	}

void parallel_chromosome::set_position(int i, vector <double> r){
		
		_chromosome[i].x=r[0];
		_chromosome[i].y = r[1];
	}
gene parallel_chromosome::get_gene(int i){
		return _chromosome[i];
	}
void parallel_chromosome::assign_positions(Random &rnd){
		if (_simtype ==0){
	
			vector <double> old_thetas;
			for (int i=0;i<_ngenes;i++){
				double theta = rnd.Rannyu(0,2*M_PI);

			
				_chromosome[i].x = cos(theta);
				_chromosome[i].y = sin(theta);

			}
			_chromosome[_ngenes].x = _chromosome[0].x;
			_chromosome[_ngenes].y = _chromosome[0].y;
		}

		if (_simtype ==1){
	
			for (int i=0;i<_ngenes;i++){
				_chromosome[i].x = rnd.Rannyu(-1,1);
				_chromosome[i].y= rnd.Rannyu(-1,1);
				

			}
				_chromosome[_ngenes].x = _chromosome[0].x;
			_chromosome[_ngenes].y = _chromosome[0].y;
		}
		if (_simtype==2){
			cout<<"Simulating shortest path between italian capoluoghi di provincia"<<endl;
			ifstream in ("cap_prov_ita.dat");
int i =0;
			while (!in.eof()){
			
			double x,y;
			in>>x>>y;	
			_chromosome[i].x = x;
			_chromosome[i].y= y;
		
				
		i++;
		}

	_chromosome[_ngenes].x = _chromosome[0].x;
			_chromosome[_ngenes].y = _chromosome[0].y;

		cout<<_chromosome.size()<<endl;
		in.close();

	}
	cout<<"Population created"<<endl;
}

void parallel_chromosome::send(int recv){
	//MPI_Datatype MPI_GENE = create_gene();
	
    MPI_Send(&_ngenes, 1, MPI_INT,recv,0,MPI_COMM_WORLD);
    MPI_Send(&_chromosome[0],_ngenes+1,MPI_gene,recv,1,MPI_COMM_WORLD);
    MPI_Send(&_cost, 1, MPI_DOUBLE,recv,2,MPI_COMM_WORLD);
	cout<<"sent "<<_ngenes<<" genes"<<endl;
}

void parallel_chromosome::receive(int sender){
	int ngenes;
    double cost;
	vector <gene> chr_vec(ngenes+1);
    MPI_Status status_n,status_ch,status_c;
    //MPI_Datatype MPI_GENE = create_gene();
    MPI_Recv(&ngenes, 1, MPI_INT,sender,0,MPI_COMM_WORLD,&status_n);
  
    cout<<"received ngenes: "<<ngenes<<endl;
    MPI_Recv(&chr_vec[0], ngenes+1, MPI_gene,sender,1,MPI_COMM_WORLD,&status_ch);
    MPI_Recv(&cost, 1, MPI_DOUBLE,sender,2,MPI_COMM_WORLD,&status_c);
	if (_ngenes != ngenes) {cerr<<"Received wrong number of genes: received "<<ngenes<<" while genes are "<<_ngenes<<endl; }
	_chromosome=chr_vec;
	_cost=cost;
}

void parallel_chromosome::permutation(Random &rnd){
    
	int rand_index1,rand_index2;
	do{
	rand_index1 = int(rnd.Rannyu(1,_ngenes));
	rand_index2 = int(rnd.Rannyu(1,_ngenes));
	} while(rand_index1==rand_index2);
	gene val = _chromosome[rand_index1];

		_chromosome[rand_index1]=_chromosome[rand_index2];
		_chromosome[rand_index2]=val;

}

void parallel_chromosome::check_bonds(){
	if (_chromosome[0].index!=0 or _chromosome[_ngenes].index!=0) cerr<<"chromosome error: first and last city must have both index 0"<<endl;
	vector <int> count_el(_ngenes,0);
	for (int i=0;i<_ngenes-1;i++){
		for (int j=0;j<_ngenes-1;j++){
			if(_chromosome[j].index==i)count_el[i]++;
		}
	if (count_el[i]>1) cerr<<"chromosome error: city "<<i<<"is repeated "<<count_el[i]<<" times"<<endl;
	}
	if(_chromosome[0].x!= _chromosome[_ngenes].x or _chromosome[0].y!= _chromosome[_ngenes].y)cerr<<"First and last positions must be fixed and the same"<<endl;


}
/*
bool chromosome::check_bonds1(){

	if (_chromosome[0].index!=0 or _chromosome[_ngenes].index!=0) return false;
	vec count_el = zeros(_ngenes);
	for (int i=0;i<_ngenes-1;i++){
		for (int j=0;j<_ngenes-1;j++){
			if(_chromosome[j].index==i)count_el[i]++;
		}
	if (count_el[i]>1) return false;
	}
	if(_chromosome[0].position[0]!= _chromosome[_ngenes].position[0] or _chromosome[0].position[1]!= _chromosome[_ngenes].position[1]) return false;
	else return true;




}*/
double parallel_chromosome::get_distance(int i1,int i2){

	double dx= _chromosome[i1].x -_chromosome[i2].x;
	double dy=_chromosome[i1].y -_chromosome[i2].y;

	return sqrt(dx*dx+dy*dy);
	

}

void parallel_chromosome::compute_cost(){
	double L1=0.; 
	//cost
	for (int i=0; i<_ngenes;i++){
		L1+= get_distance(i,i+1);
	}

	//_fitness=1./double(L1);
	_cost=L1;
}
void parallel_chromosome::print_configuration(){
	for (int i=0;i<10;i++){
		cout<<_chromosome[i].index<<" ";
	}
	cout<<endl;
}

//MUTATIONS///////////////////////////

void parallel_chromosome::shift_cities(Random &rnd){

	int c1 = int (rnd.Rannyu(1,_ngenes-1));
	int c2 = int (rnd.Rannyu(c1+1,_ngenes-1));

	int Nshifted = c2-c1+1;

	int shift_length = int(rnd.Rannyu(0,_ngenes-c2));
	

	vector <gene> copy = _chromosome;
	vector <gene> block (copy.begin()+c1,copy.begin()+c2+1);

	copy.erase(copy.begin()+c1,copy.begin()+c2+1);

	int new_pos = c1+shift_length;
	copy.insert(copy.begin()+new_pos,block.begin(),block.end());
	_chromosome=copy;
};

void parallel_chromosome::inversion(Random &rnd){
	
	int bl_start = int(rnd.Rannyu(1,_ngenes-1));
	int bl_end = int(rnd.Rannyu(bl_start+1,_ngenes));
	
	
	reverse(_chromosome.begin()+bl_start,_chromosome.begin()+bl_end+1);

}

void parallel_chromosome::block_permutation(Random &rnd){

	int block_start,block_length,block2_start;
	bool new_random = false;
	do{
	new_random=false;
	block_length= int(rnd.Rannyu(2,_ngenes/2));
	block_start = int (rnd.Rannyu(1,_ngenes-block_length));
	
	if(block_start-2>block_length) block2_start= int(rnd.Rannyu(1,block_start-2-block_length));
	else if (_ngenes-block_start-block_length-2>block_length)block2_start = int(rnd.Rannyu(block_start+block_length+1,_ngenes-block_length));
	else new_random=true;
	} while (new_random==true);

	vector <gene> block (_chromosome.begin()+block_start,_chromosome.begin()+block_start+block_length);
	vector <gene> block2 (_chromosome.begin()+block2_start,_chromosome.begin()+block2_start+block_length);

	_chromosome.erase(_chromosome.begin()+block_start,_chromosome.begin()+block_start+block_length);
	_chromosome.insert(_chromosome.begin()+block_start,block2.begin(),block2.end());

	_chromosome.erase(_chromosome.begin()+block2_start,_chromosome.begin()+block2_start+block_length);
	_chromosome.insert(_chromosome.begin()+block2_start,block.begin(),block.end());

	check_bonds();
}

void parallel_chromosome::mutation(Random &rnd){
	double p_perm = 0.1;
	double p_shift=0.1;
	double p_inv = 0.1;
	double p_blockperm =0.1;
	
	double rand_perm = rnd.Rannyu();
	if (rand_perm<p_perm) permutation(rnd);
	
	double rand_shift=rnd.Rannyu();
	if(rand_shift<p_shift) shift_cities(rnd);

	double rand_inv=rnd.Rannyu();
	if (rand_inv<p_inv) inversion(rnd);

	double rand_bl = rnd.Rannyu();
	if(rand_bl<p_blockperm) block_permutation(rnd);

}

void parallel_chromosome::cut(int start){

	_chromosome.erase(_chromosome.begin()+start,_chromosome.end()-1);

}

void parallel_chromosome::paste(vector <gene> block){
	_chromosome.insert(_chromosome.end(),block.begin(),block.end());
}

void parallel_chromosome:: crossover(int cut_pos,parallel_chromosome genitore2){
	//genitore2.print_configuration();
	vector <gene> genitore1_block (_chromosome.begin()+cut_pos,_chromosome.end()-1);
	//for (gene x: genitore1_block)cout<<x.index<<" ";
	
	vector <gene> ordered_block;
		for (gene x:genitore2.get_genevector()){
		for (gene y : genitore1_block){
			if (x.index==y.index) ordered_block.push_back(y);
		}
	}
	
	ordered_block.push_back(_chromosome[_ngenes]);
	//for (gene x:ordered_block)cout<<x.index<<" ";
	
		_chromosome.erase(_chromosome.begin()+cut_pos,_chromosome.end());
		_chromosome.insert(_chromosome.end(),ordered_block.begin(),ordered_block.end());
		
}