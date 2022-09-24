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
};