#include "continent.h"

using namespace std;

void continent::optimize(int ngen){
     cout<<"optimizing continent "<<_rank<<endl;
     _best_path= _gen.optimize(_rnd,ngen);
}
parallel_chromosome continent::get_best(){
     return _best_path;
}

void continent::migration(int receiver){

     cout<<"Migration from continent "<<_rank<<" to "<<receiver<<endl;
     _best_path.send(receiver); 
     //_best_path.receive(receiver);
     
}