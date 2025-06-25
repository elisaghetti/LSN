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
//#include "equilibration.h"
#include "color.h"
using namespace std;

int main (int argc, char *argv[]){

//UNA SOLA SIMULAZIONE (NO ISING)
if (argc==1){

  //ES 4


  int nconf = 1;
  System SYS;

  //System EQ_SYS;
  SYS.initialize();

 
  SYS.initialize_properties();
  
      if(SYS.Get_symtype() == 0)      cout <<CYAN<< "LJ MOLECULAR DYNAMICS (NVE) SIMULATION"  << RESET<<endl;
      else if(SYS.Get_symtype() == 1) cout << CYAN<<"LJ MONTE CARLO (NVT) SIMULATION"         << RESET<<endl;
      else if(SYS.Get_symtype() == 2) cout << CYAN<<"ISING 1D MONTE CARLO (MRT^2) SIMULATION" << RESET<<endl;
      else if(SYS.Get_symtype() == 3) cout << CYAN<<"ISING 1D MONTE CARLO (GIBBS) SIMULATION" <<RESET<< endl;

  //SYS.equilibrate();
 //EQUILIBRATION
 /*
   SYS.block_reset(0);
   
 cout<<YELLOW<<"Equilibration started at temperature "<<SYS.Get_Temp()<<endl;
      ofstream out("../OUTPUT/Equilibration.csv");
  out<<"Step\tTemp"<<endl;
  for (int i=0;i<2500;i++){
    SYS.step();
    SYS.measure();
    out<<i<<"\t"<<SYS.Get_Temp()<<endl;
  }
  out.close();
  cout<<"Equilibration completed at temperature T="<<SYS.Get_Temp()<<RESET<<endl;



  SYS.Reset_Averages();
cout<<"check bl"<<endl;
  //SYS.Set_Restart(1);
  //SYS.Set_Temp(ESYS.Get_Temp());


*/
 SYS.block_reset(0);
  for(int i=0; i < SYS.get_nbl(); i++){ //loop over blocks
    for(int j=0; j < SYS.get_nsteps(); j++){ //loop over steps in a block
     // out<<i*SYS.get_nsteps()+j;
      SYS.step();
       
      SYS.measure();
     
      if(j%50 == 0){ //ne stampa una ogni 50
        //SYS.write_XYZ(nconf); //Write actual configuration in XYZ format //Commented to avoid "filesystem full"!  
        nconf++;
      }
    }
    cout<<"Block "<<i<<" completed"<<endl;

  SYS.averages(i+1);
cout<<"ave"<<endl;
   SYS.block_reset(i+1);
   
  }

  SYS.finalize();
cout<<"check finalize"<<endl;


  //ES 7 
  // 
  // 
  /*

  int nconf = 1;
  System SYS;
  System EQ_SYS;

  SYS.initialize();
  SYS.initialize_properties();
 
  EQ_SYS.initialize();
  EQ_SYS.initialize_properties();

  SYS.block_reset(0);
    int eq_time=0;
  
if (SYS.Get_symtype()==0){

    //EQUILIBRATION:
 
        while(SYS.Get_Temp()>=1.1){
      SYS.step();
      SYS.measure();  
      eq_time++; 
    }
  
    cout <<YELLOW<<"Equilibration completed at temperature "<<SYS.Get_Temp()<<RESET<<endl;
    cout<<YELLOW<<"Equilibration time: "<<eq_time<<" steps"<<RESET<<endl;
    SYS.Set_Restart(1);
    SYS.block_reset(0);
    SYS.Set_Temp(1.1);
}

if (SYS.Get_symtype()==1){
  for (int i=0;i<2000;i++){
        SYS.step();
      SYS.measure();  
      eq_time++; 
  }
  cout <<YELLOW<<"Equilibration completed "<<RESET<<endl;
     cout<<YELLOW<<"Equilibration time: "<<eq_time<<" steps"<<RESET<<endl;

    SYS.Set_Restart(1);
    SYS.block_reset(0);
    SYS.Set_Temp(1.1);

}
    for(int i=0; i < SYS.get_nbl(); i++){ //loop over blocks
    for(int j=0; j < SYS.get_nsteps(); j++){ //loop over steps in a block
     // out<<i*SYS.get_nsteps()+j;
      SYS.step();
    
      SYS.measure();


      if(j%50 == 0){ //ne stampa una ogni 50
        //SYS.write_XYZ(nconf); //Write actual configuration in XYZ format //Commented to avoid "filesystem full"!  
        nconf++;
      }
    }

  SYS.averages(i+1);
  cout<<"Block "<<i+1<<" completed"<<endl;

   SYS.block_reset(i+1);
   
  }

  SYS.finalize(); */

}

//TOT SIMULAZIONI PER ISING

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

  //ISING//////////////////////////////////////////////////////////////////
  
  if(SYS.Get_symtype()>1){

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

    SYS.Change_Temp(Delta);
    SYS.Set_Restart(1);
    //if (k==0) SYS.Set_Restart(1);
    //else SYS.Set_Restart(0);
    
    cout<<"\tCompleted: "<<k+1<<endl;  
  }
}

//EX 7//////////////////////////////////////////////////////////////////////////
if (SYS.Get_symtype()<2){
  for (int k=0; k<N_sim+1;k++){
    
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

    SYS.Change_nsteps(Delta);
    SYS.Set_Restart(1);
    //if (k==0) SYS.Set_Restart(1);
    //else SYS.Set_Restart(0);
    
    cout<<"\tCompleted: "<<k+1<<endl;  
  
}
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
