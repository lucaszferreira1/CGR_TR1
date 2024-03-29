#ifndef SHAPES_H
#define SHAPES_H

struct Color{
    float r, g, b;
};
struct Vector3f{
    float x, y, z;
};
struct Vector4f{
    float r;
    struct Vector3f v;
};

struct Vector3f createVector3f(float x, float y, float z);
struct Vector4f createVector4f(float r, float x, float y, float z);
int vector3fIsEmpty(struct Vector3f v);
int vector4fIsEmpty(struct Vector4f v);

void drawBox(struct Vector3f v1, struct Vector3f v2, struct Color c);
void drawPyramid(struct Vector3f v1, struct Vector3f v2, struct Color c);
void drawPrism(struct Vector3f v1, struct Vector3f v2, struct Color c);
void drawCone(struct Vector3f v1, float radius, float height, int slices, int stacks, struct Color c);
void drawCylinder(struct Vector3f v1, struct Vector4f r, float radius, float height, int slices, int stacks, struct Color c);
void drawSphere(struct Vector3f v1, float radius, int slices, int stacks, struct Color);

#endif