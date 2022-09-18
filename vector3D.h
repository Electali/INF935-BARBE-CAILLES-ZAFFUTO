class vector3D {

    private :
        float x;
        float y;
        float z;
   
   
   public :
   
        vector3D(float i, float j, float k);

        void show();

        float norme();

};

vector3D addition(vector3D v1, vector3D v2);

vector3D multiplication(vector3D v, float lambda);

float prodScal(vector3D v1, vector3D v2);

vector3D prodVect(vector3D v1, vector3D v2);

