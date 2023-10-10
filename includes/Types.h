#pragma once

namespace OTypes{
    struct Vec3
    {
        float x, y, z;
        Vec3 operator*(float Scalar)
        {
            return Vec3{x*Scalar, y*Scalar, z*Scalar};
        }

        Vec3 operator+(Vec3 Additive){
            return Vec3{x+Additive.x, y+Additive.y, z+Additive.z};
        }
    };

    struct UV
    {
    float u, v;
    };

    struct Vertex
    {
    Vec3 Pos;
    UV TexPos;
    };

    struct Transform
    {
        Vec3 Position;
        Vec3 Scale;
        Vec3 Rotation;
    };
    
}