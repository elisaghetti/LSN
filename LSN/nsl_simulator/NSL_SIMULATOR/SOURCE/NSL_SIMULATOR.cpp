/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

#include <iostream>
#include "system.h"
#include "color.h"
using namespace std;

int main (int argc, char *argv[]){

//UNA SOLA SIMULAZIONE (NO ISING)
if (argc==1){
  int nconf = 1;
  System SYS;

  SYS.initialize();
cout<<"check_init"<<endl;



  SYS.initialize_properties();
  cout<<"check_prop"<<endl;

  SYS.block_reset(0);
  

 // ofstream out("pofv_prova.csv");
  int n_bins=SYS.get_n_bins_v();
 


  for(int i=0; i < SYS.get_nbl(); i++){ //loop over blocks
    for(int j=0; j < SYS.get_nsteps(); j++){ //loop over steps in a block
     // out<<i*SYS.get_nsteps()+j;
      SYS.step();
    
      SYS.measure();
       
     

      //se non si misura la pofv non funziona, in realtà forse non serve neanche
      //vec meas(n_bins);
      //meas.zeros();
      //SYS.Get_Measurement(meas);
      //for(int k=0;k<n_bins;k++){
        //out<<"\t"<<meas(k);
     // }
      //out<<endl;

      if(j%50 == 0){ //ne stampa una ogni 50
        //SYS.write_XYZ(nconf); //Write actual configuration in XYZ format //Commented to avoid "filesystem full"!  
        nconf++;
      }
    }

  SYS.averages(i+1);

   SYS.block_reset(i+1);
   
  }

  SYS.finalize();
cout<<"check finalize"<<endl;


  return 0;
}

//TOT SIMULAZIONI PER ISING

else{
  if (argc<4 or argc>5) cerr<<"Input number of simulations to execute and temperature interval, or no specification for only one simulation"<<endl;
  else{
    
    int N_sim = atoi(argv[1]);
    double T_min = atof(argv[2]);
    double T_max = atof(argv[3]);

    double Delta_T = (T_max-T_min)/double(N_sim);
        int nconf = 1;

  System SYS;

  SYS.initialize();


  SYS.initialize_properties();
  
  

  for (int k=0; k<N_sim+1;k++){
    SYS.Reset_Averages();


    cout<<GREEN<<"Simulation "<<k+1<<" ,"<<RED<<" T="<<SYS.Get_Temp()<<RESET<<endl;

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
    SYS.Change_Temp(-Delta_T);
    cout<<"\tCompleted: "<<k+1<<endl;

  
  }

}
    }

    return 0;
  }


/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
