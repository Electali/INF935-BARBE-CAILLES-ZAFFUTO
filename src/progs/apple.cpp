#include <iostream>
#include "../utils/vector3D.hpp"
#include "../utils/integrator.hpp"


int main(int argc, char **argv)
{
    
    if(argc != 2){
        cout << "Pour utiliser le programme, il suffit de rentrer en parametre une hauteur (en metres)." << endl;
        return 0;
    }
    
    float hauteur = (float)strtod(argv[1],NULL);


    vector3D Pomme = vector3D(0,hauteur,0); 
    vector3D VitesseChute = vector3D(0,0,0);
    vector3D Gravite = vector3D(0,-10,0);
    vector3D Newton = vector3D(0,1.63,0); 


    particle Projectile = particle(Pomme,VitesseChute,Gravite,10,0.999);
    Projectile.show();
    
    integrator Integr = integrator();


    // Delta Time fixe 

    double chrono = 0.0;
    double dt = 1.0 / 60.0;
    bool falling = true;

    while (falling)
    {
        Integr.update(Projectile,dt);
        if(Projectile.getPosition().getY() <= Newton.getY()) falling = false;
        Projectile.show(); 
        chrono += dt;
    }

/*

    // Delta Time variant

    clock_t start;
    double duration = 0; 
	double chrono = 0;
	bool falling = true;
    
    Projectile.show();


    while(falling){
        start = clock();

        Integr.update(Projectile,duration);
        Projectile.show();  // Equivalent de demander l'affichage
        cout<<endl;
		

        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
		chrono += duration;
   } 

*/ 



    cout << "La pomme a mis " << chrono << " secondes pour tomber sur Newton a partir d'une hauteur de " << hauteur << " metres." << endl;
    Projectile.show();

    
    return 0;
}