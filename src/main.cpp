#include <iostream>
#include "vector3D.hpp"
#include "integrator.hpp"

using namespace std;

int main()
{

/* TESTS DES VECTEURS */

    vector3D Reference = vector3D(0,0,0);

    vector3D Pomme = vector3D(10,3,0);

    vector3D Arbre = vector3D(10,20,0);

    vector3D Branche = vector3D(11,15,3);

    vector3D Newton = vector3D(10,1.63,0); //oui c'est vraiment sa taille 

    vector3D VitesseChute = vector3D(0,0,0);

    vector3D Gravite = vector3D(0,-10,0);

    // test fonctions d'affichage 
  
    cout << endl;
    cout << "Le refenreciel se trouve en ";
    Reference.show(); 
    cout << "La pomme se trouve en " << Pomme.getX() << " " << Pomme.getY() << " " << Pomme.getZ() <<endl;
     cout << endl;
    
    
    // normes et inverses 
   
    cout << "L'inverse du vecteur Pomme est " ;
    Pomme.inverse().show();
    Pomme.inverse();
    cout << "La norme au carre du vecteur Pomme est " << Pomme.normeCarre() << endl;
    cout << "La norme du vecteur Pomme est " << Pomme.norme() << endl;
    cout << endl;

    // additions et soustractions

    cout << "Le vecteur de Newton plus la Pomme " ; 
    addition(Pomme,Newton).show(); 
    Newton += Pomme;
    cout << " Donc l'addition des deux donne " ;
    Newton.show();

    cout << "Le vecteur de Newton moins la Pomme " ; 
    soustraction(Newton,Pomme).show(); 
    Newton -= Pomme;
    cout << " Donc la soustraction des deux donne " ;
    Newton.show();
    cout << endl; 

    // dilatation

    cout << "Wide Newton etre comme " ;
    multiplication(Newton,2).show() ;
    cout << "Donc Newton wide est ";
    Newton*=2;
    Newton.show();
    Newton*=.5;
    cout << endl;
    
    // normalisation

    cout << "Newton normalise doit etre" ;
    normalisation(Newton).show();
    cout << "Donc Newton normalise est ";
    Newton.normalise();
    Newton.show();
    cout << endl;


    // produit scalaire

    cout << "Le produit scalaire de l'arbre et de la pomme doit être :" << prodScalExt(Arbre,Pomme) << endl;
    cout << "Le produit scalaire donne " << Arbre.prodScal(Pomme) << endl;
    cout << endl;

    // produit vectoriel 

    cout << "Le produit vectoriel de l'arbre et de la pomme doit être :" ;
    prodVectExt(Arbre,Pomme).show();
    cout << "Le produit vectoriel donne ";
    Arbre.prodVect(Pomme);
    Arbre.show();
    cout << endl;


    // base orthonormee

    cout << "La base orthonormée de l'arbre, de la pomme et de la branche donne ";
    baseOrtho(Arbre,Pomme,Branche);
    Arbre.show();
    Pomme.show();
    Branche.show();


/* TESTS DES PARTICULES */
    particle Projectile = particle(Pomme,VitesseChute,Gravite,10,0.999);
    Projectile.show();
    
    integrator Integr = integrator();

    clock_t start;
    double duration = 0; 
   for(int j =0; j< 1000; j++){
    start = clock();
    Integr.update(Projectile,duration);
    cout<<endl;
    Projectile.show();
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
   } 
    
    return 0;
}

