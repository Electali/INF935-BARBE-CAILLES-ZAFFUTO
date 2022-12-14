#pragma once

#include <vector>
#include "../contacts/RigidBodyPrimitive.hpp"
#include "../contacts/RigidBodyContactPotentiel.hpp"
#include "Maths.hpp"

using namespace std;

class Octree
{

private:
    int level;
    int maxLevel = 2;
    int maxPrimitives;
    vec3 point;
    float distance;
    vector<Primitive*> whosThere;
    vector<Octree> children;

public:
    
    Octree()
    {
    }

    Octree(int lvl, int maxPri, vec3 &p, float dist, vector<Primitive*>&vP)
    {
        level = lvl;
        maxPrimitives = maxPri;
        point = p;
        distance = dist;
        whosThere = vP;
    }

    void Build(Potentiels &vexit)
    {
        // if (level >= maxLevel)
        if ((whosThere.size() <= maxPrimitives) || (level >= maxLevel))
        {
            if (whosThere.size() <= 1) return;

            
            for(int i = 0; i < whosThere.size() - 1; i++)
            {
                for(int j = i + 1; j < whosThere.size(); j++)
                {  
                    vexit.push_back(ContactPotentiel(whosThere[i], whosThere[j]));
                }
            }
            
            return;
        }
            

        vector<vec3> childPoints(8);

        float offset = distance * 0.5f;
        for (int i = 0; i < 8; i++)
        {
            childPoints[i].x = (i & 1) ? point.x + offset : point.x - offset; // On alterne un coup sur 2
            childPoints[i].y = (i & 2) ? point.y + offset : point.y - offset; // On alterne tous les 2 coups
            childPoints[i].z = (i & 4) ? point.z + offset : point.z - offset; // On alterne tous les 4 coups
        }

        vector<vector<Primitive*>> lesprimitivesdesenfantsdansunvecteurdevecteurs(8);

        for (Primitive* prim : whosThere)
        {

            for (int i = 0; i < 8; i++)
            {
                if (EstContenu(childPoints[i], offset, prim))
                    lesprimitivesdesenfantsdansunvecteurdevecteurs[i].push_back(prim);
            }
        }

        this->whosThere = {};
        for (int i = 0; i < 8; i++)
        {
            children.push_back(Octree(level + 1, maxPrimitives, childPoints[i], distance / 2, lesprimitivesdesenfantsdansunvecteurdevecteurs[i]));
            children[i].Build(vexit);
        }
    }

    void DetruireCle()
    {
    }

    int Level()
    {
        return level;
    }

    int Profondeur()
    {
        if (children.size() == 0)
            return level;
        else
            return octoMax(children[0].Profondeur(), children[1].Profondeur(), children[2].Profondeur(), children[3].Profondeur(), children[4].Profondeur(), children[5].Profondeur(), children[6].Profondeur(), children[7].Profondeur());
    }

    bool EstContenu(vec3 centre, float dist, Primitive *prim)
    {
        float distance = dist + prim->boundingBox;
    return (abs(centre.x-prim->body->rb.position.x) <= distance)
        && (abs(centre.y-prim->body->rb.position.y) <= distance)
        && (abs(centre.z-prim->body->rb.position.z) <= distance);
    }

    void AfficherEtat()
    {
        bool feuille = !children.size();
            cout << (feuille ? "La feuille" : "le noeud")
                 << " de profondeur " << level << " a " << whosThere.size() << " primitives." << endl;
            cout << "nombre d'enfants :" << children.size() << endl;
        for (Octree child : children)
        {
            child.AfficherEtat();
            cout << endl;
        }
    }

    int octoMax(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8)
    {
        int quart1 = std::max(x1, x2);
        int quart2 = std::max(x3, x4);
        int quart3 = std::max(x5, x6);
        int quart4 = std::max(x7, x8);

        int demie1 = std::max(quart1, quart2);
        int demie2 = std::max(quart3, quart4);

        int finale = std::max(demie1, demie2);

        return finale;
    }
    
    
    
};

/*    

Fonction test plus utile

bool intersect(vec3 centre, float dist, Primitive prim)
    {
        float distance = dist + prim.boundingBox;
    return (abs(centre.x-prim.body.rb.position.x) <= distance)
        && (abs(centre.y-prim.body.rb.position.y) <= distance)
        && (abs(centre.z-prim.body.rb.position.z) <= distance);
};
*/


using Pool = vector<Primitive*>;
using Children = vector<Octree>;
using Potentiels = vector<ContactPotentiel>;