#include <iostream>
#include "vector3D.hpp"
#include "integrator.hpp"

using namespace std;

int main()
{

    vector3D *Jamy = new vector3D(0,0,0);
    vector3D *Sabine = new vector3D(0,-10,0);

    vector3D Fred = vector3D(10,0,0);
    Fred.show();
   // Fred = multiplication(&Fred,3);
   // Fred.show();

    cout << prodScal(&Fred,Sabine) << "\n";

    vector3D Marcel = prodVect(&Fred,Sabine);
    Marcel.show();

    particle Camion = particle(*Jamy,Fred,*Sabine,0.1,0.999);
    Camion.show();
    
    integrator Integr = integrator();
    
    Integr.update(&Camion,1);

    Camion.show();
    
    Integr.update(&Camion,1);

    Camion.show();

    delete Jamy;
    Jamy->show();

    
    return 0;
}

