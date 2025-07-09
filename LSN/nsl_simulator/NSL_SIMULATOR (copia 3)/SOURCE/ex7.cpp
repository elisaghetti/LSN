#include <iostream>
#include "system.h"
#include "color.h"
using namespace std;

int main (int argc, char *argv[]){
    if (argc==1){ // for ex07.3 and 07.4: g(r) measurement

    int nconf = 1;
    System SYS;


    SYS.initialize();
    
    SYS.initialize_properties();

  if(SYS.Get_symtype() == 0)      cout <<CYAN<< "LJ MOLECULAR DYNAMICS (NVE) SIMULATION"  << RESET<<endl;
  else if(SYS.Get_symtype() == 1) cout << CYAN<<"LJ MONTE CARLO (NVT) SIMULATION"         << RESET<<endl;
  else if(SYS.Get_symtype() == 2) cout << CYAN<<"ISING 1D MONTE CARLO (MRT^2) SIMULATION" << RESET<<endl;
  else if(SYS.Get_symtype() == 3) cout << CYAN<<"ISING 1D MONTE CARLO (GIBBS) SIMULATION" <<RESET<< endl;

  SYS.block_reset(0);
    int eq_time=0;
  
    //EQUILIBRATION:
     if (SYS.Get_symtype()==0){
    cout<<YELLOW<<"Equilibration started at temperature "<<SYS.Get_Temp()<<endl;
    
    ofstream out;
    out.open("../OUTPUT/Equilibration_MD.csv");

    out<<"Step\tTemp"<<endl;
    for (int i=0;i<3000;i++){

        SYS.step();
        SYS.measure();
        out<<i<<"\t"<<SYS.Get_Temp()<<endl;
    }
    out.close();
    cout<<"Equilibration completed at temperature T="<<SYS.Get_Temp()<<RESET<<endl;
  }
    if (SYS.Get_symtype()==1){

      //TO DETERMINE ACCEPTANCE
      /*
      for (int i=0; i<SYS.get_nbl();i++){
        for (int j=0;j<SYS.get_nsteps();j++){
        SYS.step();
        SYS.measure();
      }
        SYS.save_acc(i+1);
        SYS.block_reset(i+1);
        SYS.change_delta(0.01);
        cout<<SYS.get_delta()<<endl;
      }
*/

      cout<<YELLOW<<"Equilibration started at energy "<<SYS.Get_PE()<<endl;
    
    ofstream out;
   out.open("../OUTPUT/Equilibration_MC.csv");
    out<<"Step\tEnergy"<<endl;
    for (int i=0;i<5000;i++){

        SYS.step();
        SYS.measure();
        out<<i<<"\t"<<SYS.Get_PE()<<endl;
    }
    out.close();
    cout<<"Equilibration completed at energy E="<<SYS.Get_PE()<<RESET<<endl;
    }
  
    SYS.Reset_Averages();
    SYS.block_reset(0); 

    for(int i=0; i < SYS.get_nbl(); i++){ //loop over blocks
    for(int j=0; j < SYS.get_nsteps(); j++){ //loop over steps in a block
     // out<<i*SYS.get_nsteps()+j;
      SYS.step();
      SYS.measure();
      if (j%1000==0)cout<<j<<endl;

      if(j%50 == 0){ //ne stampa una ogni 50
        //SYS.write_XYZ(nconf); //Write actual configuration in XYZ format //Commented to avoid "filesystem full"!  
        nconf++;
      }
    }

  SYS.averages(i+1);
  cout<<"Block "<<i+1<<" completed"<<endl;

   SYS.block_reset(i+1);
   
  }

  SYS.finalize(); 

}
else{
  if (argc<4 or argc>5) cerr<<"Input number of simulations to execute and temperature interval, or no specification for only one simulation"<<endl;
  else{
       int N_sim = atoi(argv[1]);
    double min = atof(argv[2]);
    double max = atof(argv[3]);

    double Delta = (max-min)/double(N_sim);
        int nconf = 1;

  System SYS;

  SYS.initialize();


  SYS.initialize_properties();
  for (int k=0; k<N_sim+1;k++){
    
    SYS.Set_nsteps(max-Delta*k);
    SYS.Reset_Averages();

    cout<<GREEN<<"Simulation "<<k+1<<" ,"<<RED<<" Block length="<<SYS.Get_nsteps()<<RESET<<endl;

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
    
    cout<<"\tCompleted: "<<k+1<<endl;  
  
}
}
}

    return 0;
}