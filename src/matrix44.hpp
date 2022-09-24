#pragma once

#include "vector4.hpp"
#include "vector3.hpp"

class Matrix44
{

public:
    union
    {
        struct
        {
            float xx, xy, xz, xw,
                yx, yy, yz, yw,
                zx, zy, zz, zw,
                wx, wy, wz, ww;
        };
        Vector4 data[4];
        float data2[16];
    };

    Matrix44(float val = 1)
    {
        data[0] = Vector4(val, 0, 0, 0);
        data[1] = Vector4(0, val, 0, 0);
        data[2] = Vector4(0, 0, val, 0);
        data[3] = Vector4(0, 0, 0, val);
    }

    void translate(const Vector3 &vec) {
        xw += vec.x;
        yw += vec.y;
        zw += vec.z;
    }

    void setPosition(const Vector3 &vec) {
        xw = vec.x;
        yw = vec.y;
        zw = vec.z;
    }

    operator const float* () const {
        return data2;
    }
};