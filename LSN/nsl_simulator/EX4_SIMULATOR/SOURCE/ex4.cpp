#include <iostream>
#include "system.h"
#include "color.h"
using namespace std;

int main (){

    int nconf = 1;
    System SYS;

    SYS.initialize(); //reads the input file
    SYS.initialize_properties(); //read the properties file and initializes averages array

    if(SYS.Get_symtype() == 0)      cout <<CYAN<< "LJ MOLECULAR DYNAMICS (NVE) SIMULATION"  << RESET<<endl;
    else if(SYS.Get_symtype() == 1) cout << CYAN<<"LJ MONTE CARLO (NVT) SIMULATION"         << RESET<<endl;
    else if(SYS.Get_symtype() == 2) cout << CYAN<<"ISING 1D MONTE CARLO (MRT^2) SIMULATION" << RESET<<endl;
    else if(SYS.Get_symtype() == 3) cout << CYAN<<"ISING 1D MONTE CARLO (GIBBS) SIMULATION" <<RESET<< endl;

    SYS.block_reset(0);
    
    //EQUILIBRATION: uncomment for 4.1 ////////////////////////////////////////////////////////////////////
    /*
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
    SYS.block_reset(0); //resets block accumulators to zero
    */
    ////////////////////////////////////////////////////////////////////////////////////

    for(int i=0; i <SYS.get_nbl(); i++){ //loop over blocks
        for(int j=0; j <SYS.get_nsteps(); j++){ //loop over steps in a block
        // out<<i*SYS.get_nsteps()+j;
        SYS.step();

        SYS.measure();

        if(j%50 == 0){ //ne stampa una ogni 50
            //SYS.write_XYZ(nconf); //Write actual configuration in XYZ format //Commented to avoid "filesystem full"!  
            nconf++;
            }
        }
      
       

   if(i%100==0)cout<<"Block "<<i<<" completed"<<endl;

 
    SYS.averages(i+1);
    //cout<<"ave"<<endl;
    SYS.block_reset(i+1);

    }
 //SYS.finalize();
    //EX4.3: inverting direction of time

  
    SYS.Reset_Averages();
    SYS.block_reset(0);
    SYS.time_inv();
    cout<<"Time inversion started"<<endl;

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
      
       

    if (i%100==0) cout<<"Block "<<i<<" completed"<<endl;

 
    SYS.averages(i+1);
    
    SYS.block_reset(i+1);

    }
    SYS.finalize();
    cout<<"check finalize"<<endl;
  
return 0;
}