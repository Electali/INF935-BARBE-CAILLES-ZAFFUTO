#pragma once

class Vector4
{
public:
    union
    {
        struct
        {
            float x, y, z, w;
        };
        float data[4];
        struct
        {
            float r, g, b, a;
        };
    };

    Vector4(float newX = 0, float newY = 0, float newZ = 0, float newW = 0)
    {
        x = newX;
        y = newY;
        z = newZ;
        w = newW;
    }

    operator const float* () {
        return data;
    }
};