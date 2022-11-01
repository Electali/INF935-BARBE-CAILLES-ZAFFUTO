#include "../utils/maths/Matrix34.hpp"
#include "../utils/maths/vector3.hpp"
#include "../utils/maths/Quaternion.hpp"


using namespace std;

int main(int argc, char **argv)
{
    Quaternion quat(1,0,0,0);
    vec3 vect1 = { 3, 6, 8 };
    vec3 vect2 = { 1, 0, 8 };
    vec3 vect3 = { 2, 4, 6 };

    mat3 Matrice3x3(vect1, vect2, vect3);
    Matrice3x3.show();
    cout << "\nLa transpose est : " << endl;
    (Matrice3x3.transpose()).show();
    cout << "\nL' inverse est : " << endl;
    (Matrice3x3.inverse()).show();

    cout << "\n\n//// Matrice 3x4 ////" << endl;
    mat34 mat;
    mat.setOrientationAndPosition(quat,vect2);
    mat.show();
    cout << "L'inverse est : " << endl;
    (mat.inverse()).show();

    

}