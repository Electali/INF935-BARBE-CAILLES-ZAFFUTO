#include <iostream>
#include "vector3D.h"

using namespace std;

int main(){
    vector3D Jamy = vector3D(2,3,4);
    vector3D Sabine = vector3D(8,7,6);



    vector3D Fred = addition(Jamy,Sabine);
    Fred.show();
    Fred = multiplication(Fred,3);
    Fred.show();

    cout << prodScal(Fred,Sabine) << "\n";

    vector3D Marcel = prodVect(Fred,Sabine);
    Marcel.show();

    return 0;
}

