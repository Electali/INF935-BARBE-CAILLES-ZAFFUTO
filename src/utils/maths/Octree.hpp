#pragma once

#include <vector>

using namespace std;

class Octree {
    vec3 point;

    vec3 *topLeftFront, *bottomRightBack;
    vector<Octree*> children;
}