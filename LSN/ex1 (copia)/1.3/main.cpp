//ESERCIZIO 1.3

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h"

using namespace std;
int main() {
double l= 0.07; //needle lenght
double D = 0.1;

int N_throws = 1000000;
int N_hit =0;
//considero cerchio di raggio unitario come piano

for(int i=0; i<N_throws; i++){

   double r_1= rnd.Rannyu();

   double sin_theta= rnd.Rannyu(-1,1); //angolo all'origine: sintheta è l'altezza a cui si trova il primo vertice della barretta
   double sin_psi= rnd.Rannyu(-1.,1.); //angolo di inclinazione, quindi ottenuto spostando l'origine in (r_1, theta)

   if(sin_psi >=0) {

      double h_low= r_1*sin_theta; // altezza del vertice più basso;
      double h_high = h_low + l* sin_psi; // altezza del vertice superiore della barretta
//double h_high = h_low +rnd.Rannyu(0,l);
      int d=0;
      while(-1+d*D <=1.){

         if ( h_high>=-1+D*d && h_low <= -1+d*D) {
         N_hit++;
         break;
         }
      d++;
      }
   }

   else {
      
      double h_high= r_1*sin_theta; // altezza del vertice più basso;
      double h_low = h_high + l* sin_psi; // altezza del vertice superiore della barretta
      //double h_high = h_low +rnd.Rannyu(0,l);

      int d=0;
      while(-1+d*D<=1.){
         if (h_high>=-1+D*d && h_low <=-1+ d*D) {
            N_hit++;
            break;
         }
      d++;
      }
   }

 
}
cout<<N_hit<<" "<< double(2*l*N_throws)/(N_hit*D)<<endl;

return 0;

}