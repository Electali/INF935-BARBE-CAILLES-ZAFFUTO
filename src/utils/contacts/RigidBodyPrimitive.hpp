#pragma once
#include "../RigidBody3D.hpp"
#include "../maths/Maths.hpp"
#include "RigidbodyContact.hpp"


#include <vector>

class Sphere;
class Box;
class Plane;

class Primitive
{
public:

    Primitive()
    {
    }
    
    virtual ~Primitive() {}


    virtual void show() = 0;

    virtual void GenerateContactSphere(Sphere *p, vector<Contact*>& cd,int maxContacts) = 0;

    virtual void GenerateContactBox(Box *p, vector<Contact*>& cd,int maxContacts) = 0;

    virtual void GenerateContactPlane(Plane *p, vector<Contact*>& cd,int maxContacts) = 0;

    RigidBody3D body;
    float boundingBox;

};

class Sphere : public Primitive 
{
public:
    float radius;

    Sphere(RigidBody3D &_body, float _boundingBox, float _radius)
    {
        body = _body;
        boundingBox = _boundingBox;
        radius = _radius;
    }

    ~Sphere(){};

    void show(){};

    void GenerateContactSphere(Sphere *s2, vector<Contact*>& cd,int maxContacts)
    {
        /////Check Place
        if(cd.size() >= maxContacts) return;

        ////Check si collision
        cout << "Début Generate" << endl;
        vec3 positionOne = body.rb.position;
        positionOne.show();
        vec3 positionTwo = s2->body.rb.position;
        positionTwo.show();
        vec3 midline = positionOne - positionTwo;
        midline.show();
        float size = midline.norme();
        cout << size << endl;

        // Si Vrai => Sphere non en contact => Pas de collision 
        if ((size <= 0.0f) || (size >= radius + s2->radius)) 
        {
            cout << "Tchao baye baye" << endl;
            return ;
        }

        // Si Faux => On crée le contact
        
        vec3 polPot = midline * 0.5f;
        polPot += positionOne;

        vec3 midTown = midline * (1.0f/size);
        
        Contact * contact = new Contact(
            polPot, //Position
            midTown, //Normal
            radius + s2->radius - size, //Interpenetration
            body.rb, //RigidB1
            s2->body.rb, //RigidB2;
            FaceFace); //TypeContact
        cd.push_back(contact);
    };

    void GenerateContactBox(Box *p, vector<Contact*>& cd,int maxContacts)
    {
        cout << "TG S B" << endl;
    };

    void GenerateContactPlane(Plane *p, vector<Contact*>& cd,int maxContacts)
    {
        cout << "TG S P " << endl;
    };
};

class Box : public Primitive
{
public:

   vec3 halfSize;
   vec3 vertices [8];
    Box(RigidBody3D &_body, float _boundingBox, vec3 &_halfsize)
   {
      body = _body;
      boundingBox = _boundingBox;
      halfSize = _halfsize;

      for (int i = 0; i < 8; i++)
        {
         int x = (i & 4) ? halfSize.x : -halfSize.x;   // On alterne tous les 4 coups
         int y = (i & 2) ? halfSize.y : -halfSize.y;   // On alterne tous les 2 coups
         int z = (i & 1) ? halfSize.z : -halfSize.z;   // On alterne un coup sur 2
         vertices[i] = vec3(x,y,z);
        }
   }

    virtual ~Box();

    void GenerateContactSphere(Sphere *p, vector<Contact*>& cd,int maxContacts)
    {
        cout << "TG B S " << endl;
    };

    void GenerateContactBox(Box *p, vector<Contact*>& cd,int maxContacts)
    {
        cout << "TG B B" << endl;
    };

    void GenerateContactPlane(Plane *p, vector<Contact*>& cd,int maxContacts)
    {
        cout << "TG B P " << endl;
    };

};

class Plane : public Primitive
{
    public:
    vec3 normal;
    float planeOffset;

    Plane(RigidBody3D &_body,float _boundingBox , vec3 _normal, float _planeOffset)
    {
        body = _body;
        boundingBox = _boundingBox;
        normal = _normal;
        planeOffset = _planeOffset;
    }

    virtual ~Plane();

    void GenerateContactSphere(Sphere *p, vector<Contact*>& cd,int maxContacts)
    {
        cout << "TG P S " << endl;
    };

    void GenerateContactBox(Box *p, vector<Contact*>& cd,int maxContacts)
    {
        cout << "TG P B" << endl;
    };

    void GenerateContactPlane(Plane *p, vector<Contact*>& cd,int maxContacts)
    {
        cout << "TG P P " << endl;
    };
};

