#include <cmath>
#include <cstdlib>
#include <string>
#include "system.h"
#include "color.h"

using namespace std;
using namespace arma;

Equilibration :: void Equilibrate_MD(target_temp){
while(_SYS.Get_Temp()<target_temp){
      _SYS.step();
      _SYS.measure();  
    }
cout<<"System equilibrated at temperature T="<<_SYS.Get_Temp<<endl;
}