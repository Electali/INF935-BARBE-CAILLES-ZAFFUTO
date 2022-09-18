#include <iostream>
#include <math.h>
#include "vector3D.h"

using namespace std;

vector3D::vector3D(float i, float j, float k){
    x = i;
    y = j;
    z = k;
}

void vector3D::show(){
cout << "(" << this->x << "," << this->y << "," << this->z << ")\n";
}

float vector3D::norme(){
    float res = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
    return res;
}

vector3D addition(vector3D v1, vector3D v2){
    return vector3D((v1.x+v2.x),(v1.y+v2.y),(v1.z+v2.z));
}


vector3D multiplication(vector3D v, float lambda){
    return vector3D(v.x*lambda,v.y*lambda,v.z*lambda);
}

float prodScal(vector3D v1, vector3D v2){
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}


vector3D prodVect(vector3D v1, vector3D v2){
    return vector3D( (v1.y*v2.z - v1.z*v2.y), (v1.z*v2.x - v1.x*v2.z) , (v1.x*v2.y - v1.y*v2.x));
}

