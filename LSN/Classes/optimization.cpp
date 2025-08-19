#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <armadillo>
#include <random.h>
#include "system.h"
#include "particle.h"
#include "color.h"
using namespace std;
using namespace arma;


void optimizer::simulated_annealing(system SYS, double Tmax, double Tmin, int Tsteps){
    
    double Delta = fabs(Tmax-Tmin)/double(Tsteps);
    int nconf = 1;
   
    SYS.initialize();
    SYS.initialize_properties();
  
    //loop that slowly lowers system temperature
    for (int k=0; k<N_sim+1;k++){
    SYS.Set_Temp(Tmax-Delta*k);

        
    cout<<GREEN<<"Simulation "<<k+1<<" ,"<<RED<<" T="<<SYS.Get_Temp()<<RESET<<endl;
       SYS.Reset_Averages();
       SYS.block_reset(0);
    for(int i=0; i < SYS.get_nbl(); i++){ //loop over blocks
       for(int j=0; j < SYS.get_nsteps(); j++){ //loop over steps in a block
        SYS.step(); 
        SYS.measure();
      }
  
      SYS.averages(i+1);
      SYS.block_reset(i+1);
    }

    SYS.finalize();
    SYS.Set_Restart(1);
    cout<<"\tCompleted: "<<k+1<<endl;  
  }
}



}