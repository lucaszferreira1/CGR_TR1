#ifndef SHAPES_H
#define SHAPES_H

struct Color{
    float r, g, b;
};
struct Vector3f{
    float x, y, z;
};

struct Vector3f createVector3f(float x, float y, float z);

void drawBox(struct Vector3f v1, struct Vector3f v2, struct Color c);
void drawPyramid(struct Vector3f v1, struct Vector3f v2, struct Color c);
void drawPrism(struct Vector3f v1, struct Vector3f v2, struct Color c);
void drawCone(struct Vector3f v1, float radius, float height, int slices, int stacks, struct Color c);
void drawCylinder(struct Vector3f v1, float radius, float height, int slices, int stacks, struct Color c);
void drawSphere(struct Vector3f v1, float radius, int slices, int stacks, struct Color);

#endif