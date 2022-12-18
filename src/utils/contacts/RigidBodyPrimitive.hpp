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

    RigidBody3D * body;
    float boundingBox;

};





class Plane : public Primitive
{
    public:
    vec3 normal;
    float planeOffset;

    Plane(RigidBody3D * _body,float _boundingBox , vec3 _normal, float _planeOffset)
    {
        body = _body;
        boundingBox = _boundingBox;
        normal = _normal;
        planeOffset = _planeOffset;
        body->cube= Cube();
        body->trans.setScale(500, 0.001, 500);
    }

    ~Plane(){};

    void show(){};

    virtual void GenerateContactSphere(Sphere *s2, vector<Contact*>& cd,int maxContacts);

    virtual void GenerateContactBox(Box *b2, vector<Contact*>& cd,int maxContacts);

    virtual void GenerateContactPlane(Plane *p2, vector<Contact*>& cd,int maxContacts);
    
};


class Sphere : public Primitive 
{
public:
    float radius;

    Sphere(RigidBody3D *_body, float _boundingBox, float _radius)
    {
        body = _body;
        boundingBox = _boundingBox;
        radius = _radius;
        body->isCube = false;
        body->trans.setScale(radius, radius, radius);
    }

    ~Sphere(){};

    void show(){};

    virtual void GenerateContactSphere(Sphere *s2, vector<Contact*>& cd,int maxContacts);

    virtual void GenerateContactBox(Box *b2, vector<Contact*>& cd,int maxContacts);
    
    virtual void GenerateContactPlane(Plane *p2, vector<Contact*>& cd,int maxContacts);

};

class Box : public Primitive
{
public:

   vec3 halfSize;
   vec3 vertices [8];
    Box(RigidBody3D *_body, float _boundingBox, vec3 &_halfsize)
   {
      body = _body;
      boundingBox = _boundingBox;
      halfSize = _halfsize;

      for (int i = 0; i < 8; i++)
        {
         float x = body->rb.position.x + ((i & 4) ? halfSize.x : -halfSize.x);   // On alterne tous les 4 coups
         float y = body->rb.position.y + ((i & 2) ? halfSize.y : -halfSize.y);   // On alterne tous les 2 coups
         float z = body->rb.position.z + ((i & 1) ? halfSize.z : -halfSize.z);   // On alterne un coup sur 2
         vertices[i] =  {x,y,z};
        }
        body->trans.setScale(halfSize.x, halfSize.y, halfSize.z);
   }

    ~Box() {};

    void show(){};

    virtual void GenerateContactSphere(Sphere *s2, vector<Contact*>& cd,int maxContacts);

    virtual void GenerateContactBox(Box *b2, vector<Contact*>& cd,int maxContacts);
    
    virtual void GenerateContactPlane(Plane *p2, vector<Contact*>& cd,int maxContacts);

};





void Plane::GenerateContactSphere(Sphere *s2, vector<Contact*>& cd,int maxContacts)
    {
        s2->GenerateContactPlane(this,cd,maxContacts);
    };

    void Plane::GenerateContactBox(Box *b2, vector<Contact*>& cd,int maxContacts)
    {
        b2->GenerateContactPlane(this,cd,maxContacts);
    };

    void Plane::GenerateContactPlane(Plane *p2, vector<Contact*>& cd,int maxContacts)  
    { }; // n'existe pas dans notre cas


void Sphere::GenerateContactSphere(Sphere *s2, vector<Contact*>& cd,int maxContacts)
    {
        /////Check Place
        if(cd.size() >= maxContacts) return;

        ////Check si collision
        cout << "Début Generate" << endl;
        vec3 positionOne = body->rb.position;
        positionOne.show();
        vec3 positionTwo = s2->body->rb.position;
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
            body->rb, //RigidB1
            s2->body->rb, //RigidB2;
            FaceFace); //TypeContact
        cd.push_back(contact);
    }

    void Sphere::GenerateContactBox(Box *b2, vector<Contact*>& cd,int maxContacts)
    {
        b2->GenerateContactSphere(this,cd,maxContacts);
    }
    
    void Sphere::GenerateContactPlane(Plane *p2, vector<Contact*>& cd,int maxContacts)
    {
        /////Check Place
        if(cd.size() >= maxContacts) return;

        vec3 centreSphere = body->rb.position;
        vec3 normal = p2->normal;
        float dist = prodScalExt(centreSphere, normal) - p2->planeOffset;
        
        // Si Vrai => Pas de contact 
        if(dist > radius) return;

        //Si Faux => Création du contact
        vec3 cp = centreSphere - (normal * (dist + radius));
        Contact * contact = new Contact(
            cp, //Position
            normal, //Normal
            -dist, // Interpenetration
            body->rb, //RigidB1
            p2->body->rb, //RigidB2
            FaceFace); //TypeContact
        cd.push_back(contact);
    }

void Box::GenerateContactSphere(Sphere *s2, vector<Contact*>& cd,int maxContacts)
    {
        /////Check Place
        if(cd.size() >= maxContacts) return;

        vec3 spCenterBx = body->rb.WorldToLocal(s2->body->rb.position);

        //Check rapide contact
        if ( abs(spCenterBx.x) - s2->radius > halfSize.x ||
             abs(spCenterBx.y) - s2->radius > halfSize.y ||
             abs(spCenterBx.z) - s2->radius > halfSize.z
        ) return ;

        // Calcul du point le plus proche 
        vec3 closestPt = {};
        float distance; 

        distance = spCenterBx.x;
        if( distance > halfSize.x) distance = halfSize.x;
        if( distance < -halfSize.x) distance = -halfSize.x;
        closestPt.x = distance;

        distance = spCenterBx.y;
        if( distance > halfSize.y) distance = halfSize.y;
        if( distance < -halfSize.y) distance = -halfSize.y;
        closestPt.y = distance;

        distance = spCenterBx.z;
        if( distance > halfSize.z) distance = halfSize.z;
        if( distance < -halfSize.z) distance = -halfSize.z;
        closestPt.z = distance;

        distance = (closestPt - spCenterBx).norme();
        //Check collision
        if (distance > s2->radius * s2->radius) return ;

        // SI collision creation contact
        vec3 closestPtWorld = body->rb.LocalToWorld(closestPt);
        vec3 normal = (closestPtWorld - s2->body->rb.position);
        normal.normalise();
        Contact * contact = new Contact(
            closestPtWorld, // Position
            normal, //Normal
            s2->radius - sqrt(distance), // Interpenetration
            s2->body->rb, //RigidB1
            body->rb, //RigidB2
            PointFace); //TypeContact    //3 types de contact mais d'après livre, pas important donc choix = type le plus prioritaire dans la résolution.            
        cd.push_back(contact);
    }

    void Box::GenerateContactBox(Box *b2, vector<Contact*>& cd,int maxContacts)
    {
        /*
        /////Check Place
        if(cd.size() >= maxContacts) return;
        
        float bestOverlap = 9999999999;
        unsigned int bestCase;

        for(unsigned int i = 0; i<15; i++)
        {
            vec3 
        }
        */
    }
    
    void Box::GenerateContactPlane(Plane *p2, vector<Contact*>& cd,int maxContacts)
    {
        body->rb.position.show();
        //Recalcul des sommets 
        for (int i = 0; i < 8; i++)
            {
                float x = body->rb.position.x + ((i & 4) ? halfSize.x : -halfSize.x);   // On alterne tous les 4 coups
                float y = body->rb.position.y + ((i & 2) ? halfSize.y : -halfSize.y);   // On alterne tous les 2 coups
                float z = body->rb.position.z + ((i & 1) ? halfSize.z : -halfSize.z);   // On alterne un coup sur 2
                vertices[i] = {x,y,z};
            }
        
        for(int i =0; i < 8; i++)       // On test chaque sommet de la boite un par un.
        {
            /////Check Place
            if(cd.size() >= maxContacts) return ; // Plus de place pour générer un contact

            
            
            vec3 vertice = body->rb.LocalToWorld(vertices[i]) ; //Transformation LocaltoWorld du point
            //vertice.show();
            float vertDist = prodScalExt(vertice,p2->normal);
            if (vertDist < p2->planeOffset) {// Si vrai alors création du contact

            vec3 cp = p2->normal * (vertDist - p2->planeOffset) + body->rb.position;
            float inter = p2->planeOffset - vertDist;

            Contact * contact = new Contact(
            vertice, //Position
            p2->normal, //Normal
            inter, // Interpenetration
            p2->body->rb, //RigidB1
            body->rb, //RigidB2
            PointFace); //TypeContact
            cd.push_back(contact);
            }
        }
    };