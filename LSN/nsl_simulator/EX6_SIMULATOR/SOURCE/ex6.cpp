#include <iostream>
#include "system.h"
#include "color.h"
using namespace std;

int main (int argc, char *argv[]){
    if (argc<4 or argc>5) cerr<<"Input number of simulations to execute and temperature interval, or no specification for only one simulation"<<endl;
  else{
    
    int N_sim = atoi(argv[1]);
    double min = atof(argv[2]);
    double max = atof(argv[3]);
    double Delta = fabs(max-min)/double(N_sim);
    int nconf = 1;



  System SYS;

  SYS.initialize();
  SYS.initialize_properties();

  if(SYS.Get_symtype() == 0)      cout <<CYAN<< "LJ MOLECULAR DYNAMICS (NVE) SIMULATION"  << RESET<<endl;
  else if(SYS.Get_symtype() == 1) cout << CYAN<<"LJ MONTE CARLO (NVT) SIMULATION"         << RESET<<endl;
  else if(SYS.Get_symtype() == 2) cout << CYAN<<"ISING 1D MONTE CARLO (MRT^2) SIMULATION" << RESET<<endl;
  else if(SYS.Get_symtype() == 3) cout << CYAN<<"ISING 1D MONTE CARLO (GIBBS) SIMULATION" <<RESET<< endl;

  if(SYS.Get_symtype()>1){

  for (int k=0; k<N_sim+1;k++){
    //SYS.CheckSizes();
    SYS.Set_Temp(max-Delta*k);

      //SYS.Change_Temp(-Delta);

    cout<<GREEN<<"Simulation "<<k+1<<" ,"<<RED<<" T="<<SYS.Get_Temp()<<RESET<<endl;
   // SYS.CheckSizes();
       SYS.Reset_Averages();
      SYS.block_reset(0);
    for(int i=0; i < SYS.get_nbl(); i++){ //loop over blocks
      for(int j=0; j < SYS.get_nsteps(); j++){ //loop over steps in a block

        SYS.step();
      
        SYS.measure();

        if(j%50 == 0){ //ne stampa una ogni 50
          //SYS.write_XYZ(nconf); //Write actual configuration in XYZ format //Commented to avoid "filesystem full"!  
          nconf++;
        }
      }
  
      SYS.averages(i+1);
      SYS.block_reset(i+1);
    }

    SYS.finalize();
    SYS.Set_Restart(1);

    //if (k==0) SYS.Set_Restart(1);
    //else SYS.Set_Restart(0);
    //cout<<SYS.Get_Temp()<<endl;
    cout<<"\tCompleted: "<<k+1<<endl;  
  }
}
  else cerr<<"This is the main code for simulating Ising model(ex 6), input simulation type 2(metropolis) or 3 (gibbs)"<<endl;
return 0;
  }

  }