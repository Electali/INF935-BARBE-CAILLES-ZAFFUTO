#pragma once
#include <vector>

#include "RigidBodySphere.hpp"
#include "RigidBodyBox.hpp"
#include "RigidBodyPlan.hpp"
#include "RigidBodyContact.hpp"


class ContactGenerator
{

    ContactGenerator()
    {}

    //page 307 du livre Millington
    void GenerateContacts(Sphere s1, Sphere s2,vector<Contact*>& cd,int maxContacts)
    {
        /////Check Place
        if(cd.size() >= maxContacts) return;

        ////Check si collision

        vec3 positionOne = s1.body.rb.position;
        vec3 positionTwo = s2.body.rb.position;
        vec3 midline = positionOne - positionTwo;
        float size = midline.norme();

        // Si Vrai => Sphere non en contact => Pas de collision 
        if ((size <= 0.0f) || (size >= s1.radius + s2.radius)) return ;

        // Si Faux => On crée le contact
        
        Contact * contact = new Contact(
            positionOne + (midline * 0.5f), //Position
            midline * (1.0f/size), //Normal
            s1.radius + s2.radius - size, //Interpenetration
            s1.body.rb, //RigidB1
            s2.body.rb, //RigidB2;
            FaceFace); //TypeContact
        cd.push_back(contact);
    }

    void GenerateContacts(Sphere s1, Plane p2,vector<Contact*>& cd,int maxContacts)
    {
        /////Check Place
        if(cd.size() >= maxContacts) return;

        vec3 centreSphere = s1.body.rb.position;
        vec3 normal = p2.normal;
        float dist = prodScalExt(centreSphere, normal) - p2.planeOffset;
        
        // Si Vrai => Pas de contact 
        if(dist > s1.radius) return;

        //Si Faux => Création du contact
        vec3 cp = centreSphere - (normal * (dist + s1.radius));
        Contact * contact = new Contact(
            cp, //Position
            normal, //Normal
            -dist, // Interpenetration
            s1.body.rb, //RigidB1
            p2.body.rb, //RigidB2
            FaceFace); //TypeContact
        cd.push_back(contact);


    }

    void GenerateContacts(Plane p1, Sphere s2,vector<Contact*>& cd,int maxContacts)
    {
        GenerateContacts(s2,p1,cd,maxContacts);
    }


    void GenerateContacts(Sphere s1, Box b2,vector<Contact*>& cd,int maxContacts)
    {
        /////Check Place
        if(cd.size() >= maxContacts) return;

        vec3 spCenterBx = b2.body.rb.WorldToLocal(s1.body.rb.position);

        //Check rapide contact
        if ( abs(spCenterBx.x) - s1.radius > b2.halfSize.x ||
             abs(spCenterBx.y) - s1.radius > b2.halfSize.y ||
             abs(spCenterBx.z) - s1.radius > b2.halfSize.z
        ) return ;



        /* TO DO */



    }

    void GenerateContacts(Box b1, Sphere s2,vector<Contact*>& cd,int maxContacts)
    {
        GenerateContacts(s2,b1,cd,maxContacts);
    }

    void GenerateContacts(Plane p1, Box b2,vector<Contact*>& cd,int maxContacts)
    {
        for(int i =0; i < 8; i++)       // On test chaque sommet de la boite un par un.
        {
            /////Check Place
            if(cd.size() >= maxContacts) return;

            vec3 vertice = b2.body.rb.LocalToWorld(b2.vertices[i]) ; //Transformation LocaltoWorld du point
            float vertDist = prodScalExt(vertice,p1.normal);
            if (vertDist > p1.planeOffset) return; // Pas d'intersection avec le plan. => Pas de contact

            //Creation du contact

            vec3 cp = p1.normal * (vertDist - p1.planeOffset) + b2.body.rb.position;
            float inter = p1.planeOffset - vertDist;

            Contact * contact = new Contact(
            cp, //Position
            p1.normal, //Normal
            inter, // Interpenetration
            p1.body.rb, //RigidB1
            b2.body.rb, //RigidB2
            PointFace); //TypeContact
            cd.push_back(contact);
        }
           
    }

    void GenerateContacts(Box b1, Plane p2, vector<Contact*>& cd,int maxContacts)
    {
        GenerateContacts(p2, b1, cd, maxContacts);   
    }

    void GenerateContacts(Box b1, Box b2,vector<Contact*>& cd,int maxContacts)
    {
        /////Check Place
        if(cd.size() >= maxContacts) return;
        
    }
};