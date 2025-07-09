#ifndef __Equilibration__
#define __Equilibration__

#include "system.h"

using namespace std;
using namespace arma;

class Equilibration {

private:
    System _SYS;
    double _targetT,_initialT;

public:

    Equilibration();
    Equilibration(System SYS) {_SYS=SYS;};

    void Equilibrate_MD();
    void Equilibrate_Ising();
    void Equilibrate_MC();

    
};

#endif