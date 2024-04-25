#ifndef SHAPES_H
#define SHAPES_H

struct Color{
    float r, g, b, a;
};
struct Vector3f{
    float x, y, z;
};

typedef struct Color Color;
typedef struct Vector3f Vector3f;

Vector3f createVector3f(float x, float y, float z);
int vector3fIsEmpty( Vector3f v);

void drawBox(Vector3f v1, Vector3f v2, Color c);
void drawPyramid(Vector3f v1, Vector3f v2, Color c);
void drawPrism(Vector3f v1, Vector3f v2, Color c);
void drawCone(Vector3f v1, Vector3f r, float radius, float height, int slices, int stacks, Color c);
void drawCylinder(Vector3f v1, Vector3f r, float radius, float height, int slices, int stacks, Color c);
void drawSphere(Vector3f v1, float radius, int slices, int stacks, Color);

#endif
