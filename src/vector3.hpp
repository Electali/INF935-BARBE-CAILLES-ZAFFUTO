#pragma once

class Vector3
{
public:
    union
    {
        struct
        {
            float x, y, z;
        };
        float data[3];
        struct
        {
            float r, g, b;
        };
    };

    Vector3(float newX = 0, float newY = 0, float newZ = 0)
    {
        x = newX;
        y = newY;
        z = newZ;
    }

    friend Vector3 addition(Vector3 &v1, Vector3 &v2)
    {
        return Vector3((v1.x + v2.x), (v1.y + v2.y), (v1.z + v2.z));
    }
};