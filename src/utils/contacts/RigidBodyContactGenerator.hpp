#pragma once
#include <vector>

#include "RigidBodyContact.hpp"
#include "RigidBodyContactPotentiel.hpp"
#include "RigidBodyPrimitive.hpp"

using namespace std;
class ContactGenerator
{
    public: Potentiels potentials;
    
    ContactGenerator(Potentiels pot)
    {
        potentials = pot;
    }

    void Generate(vector<Contact*>& cd, int max)
    {
        for(ContactPotentiel pot: potentials){ 
            if (dynamic_cast<Sphere *>(pot.Prim2)){
                Sphere * s2 = dynamic_cast<Sphere *>(pot.Prim2);
                pot.Prim1->GenerateContactSphere(s2,cd,max);
            }
            else if (dynamic_cast<Box *>(pot.Prim2)){
                Box * b2 = dynamic_cast<Box *>(pot.Prim2);
                pot.Prim1->GenerateContactBox(b2,cd,max);
            }
            else {
                Plane * p2 = dynamic_cast<Plane *>(pot.Prim2);
                pot.Prim1->GenerateContactPlane(p2,cd,max);
            }

        }
    }
/*
    void GenerateContacts(Sphere * s1, Sphere * s2,vector<Contact*>& cd,int maxContacts)
    {
        /////Check Place
        if(cd.size() >= maxContacts) return;

        ////Check si collision
        cout << "Début Generate" << endl;
        vec3 positionOne = s1->body.rb.position;
        positionOne.show();
        vec3 positionTwo = s2->body.rb.position;
        positionTwo.show();
        vec3 midline = positionOne - positionTwo;
        midline.show();
        float size = midline.norme();
        cout << size << endl;

        // Si Vrai => Sphere non en contact => Pas de collision 
        if ((size <= 0.0f) || (size >= s1->radius + s2->radius)) 
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
            s1->radius + s2->radius - size, //Interpenetration
            s1->body.rb, //RigidB1
            s2->body.rb, //RigidB2;
            FaceFace); //TypeContact
        cd.push_back(contact);
    }

    void GenerateContacts(Sphere * s1, Plane * p2,vector<Contact*>& cd,int maxContacts)
    {
        /////Check Place
        if(cd.size() >= maxContacts) return;

        vec3 centreSphere = s1->body.rb.position;
        vec3 normal = p2->normal;
        float dist = prodScalExt(centreSphere, normal) - p2->planeOffset;
        
        // Si Vrai => Pas de contact 
        if(dist > s1->radius) return;

        //Si Faux => Création du contact
        vec3 cp = centreSphere - (normal * (dist + s1->radius));
        Contact * contact = new Contact(
            cp, //Position
            normal, //Normal
            -dist, // Interpenetration
            s1->body.rb, //RigidB1
            p2->body.rb, //RigidB2
            FaceFace); //TypeContact
        cd.push_back(contact);


    }

    void GenerateContacts(Plane * p1, Sphere * s2,vector<Contact*>& cd,int maxContacts)
    {
        GenerateContacts(s2,p1,cd,maxContacts);
    }


    void GenerateContacts(Sphere * s1, Box * b2,vector<Contact*>& cd,int maxContacts)
    {
        /////Check Place
        if(cd.size() >= maxContacts) return;

        vec3 spCenterBx = b2->body.rb.WorldToLocal(s1->body.rb.position);

        //Check rapide contact
        if ( abs(spCenterBx.x) - s1->radius > b2->halfSize.x ||
             abs(spCenterBx.y) - s1->radius > b2->halfSize.y ||
             abs(spCenterBx.z) - s1->radius > b2->halfSize.z
        ) return ;

        // Calcul du point le plus proche 
        vec3 closestPt = {};
        float distance; 

        distance = spCenterBx.x;
        if( distance > b2->halfSize.x) distance = b2->halfSize.x;
        if( distance < -b2->halfSize.x) distance = -b2->halfSize.x;
        closestPt.x = distance;

        distance = spCenterBx.y;
        if( distance > b2->halfSize.y) distance = b2->halfSize.y;
        if( distance < -b2->halfSize.y) distance = -b2->halfSize.y;
        closestPt.y = distance;

        distance = spCenterBx.z;
        if( distance > b2->halfSize.z) distance = b2->halfSize.z;
        if( distance < -b2->halfSize.z) distance = -b2->halfSize.z;
        closestPt.z = distance;

        distance = (closestPt - spCenterBx).norme();
        //Check collision
        if (distance > s1->radius * s1->radius) return ;

        // SI collision creation contact
        vec3 closestPtWorld = b2->body.rb.LocalToWorld(closestPt);
        vec3 normal = (closestPtWorld - s1->body.rb.position);
        normal.normalise();
        Contact * contact = new Contact(
            closestPtWorld, // Position
            normal, //Normal
            s1->radius - sqrt(distance), // Interpenetration
            s1->body.rb, //RigidB1
            b2->body.rb, //RigidB2
            PointFace); //TypeContact    //3 types de contact mais d'après livre, pas important donc choix = type le plus prioritaire dans la résolution.            
        cd.push_back(contact);
    }

    void GenerateContacts(Box * b1, Sphere * s2,vector<Contact*>& cd,int maxContacts)
    {
        GenerateContacts(s2,b1,cd,maxContacts);
    }

    void GenerateContacts(Plane * p1, Box * b2,vector<Contact*>& cd,int maxContacts)
    {
        for(int i =0; i < 8; i++)       // On test chaque sommet de la boite un par un.
        {
            /////Check Place
            if(cd.size() >= maxContacts) return;

            vec3 vertice = b2->body.rb.LocalToWorld(b2->vertices[i]) ; //Transformation LocaltoWorld du point
            float vertDist = prodScalExt(vertice,p1->normal);
            if (vertDist > p1->planeOffset) return; // Pas d'intersection avec le plan. => Pas de contact

            //Creation du contact

            vec3 cp = p1->normal * (vertDist - p1->planeOffset) + b2->body.rb.position;
            float inter = p1->planeOffset - vertDist;

            Contact * contact = new Contact(
            cp, //Position
            p1->normal, //Normal
            inter, // Interpenetration
            p1->body.rb, //RigidB1
            b2->body.rb, //RigidB2
            PointFace); //TypeContact
            cd.push_back(contact);
        }
           
    }

    void GenerateContacts(Box * b1, Plane * p2, vector<Contact*>& cd,int maxContacts)
    {
        GenerateContacts(p2, b1, cd, maxContacts);   
    }

    /*
    void GenerateContacts(Box b1, Box b2,vector<Contact*>& cd,int maxContacts)
    {
        /////Check Place
        if(cd.size() >= maxContacts) return;
        
        float bestOverlap = 9999999999;
        unsigned int bestCase;

        for(unsigned int i = 0; i<15; i++)
        {
            vec3 
        }
    }
    */
};

