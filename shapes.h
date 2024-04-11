#ifndef SHAPES_H
#define SHAPES_H

struct Color{
    float r, g, b;
};
struct Vector3f{
    float x, y, z;
};
struct Vector4f{
    struct Vector3f v;
    float r;
};
struct Particle{
    struct Vector3f pos, vel, col;
    float lifetime;
};

struct Vector3f createVector3f(float x, float y, float z);
struct Vector4f createVector4f(float r, float x, float y, float z);
int vector3fIsEmpty(struct Vector3f v);
int vector4fIsEmpty(struct Vector4f v);

void drawBox(struct Vector3f v1, struct Vector3f v2, struct Color c);
void drawPyramid(struct Vector3f v1, struct Vector3f v2, struct Color c);
void drawPrism(struct Vector3f v1, struct Vector3f v2, struct Color c);
void drawCone(struct Vector3f v1, float r[3], float radius, float height, int slices, int stacks, struct Color c);
void drawCylinder(struct Vector3f v1, float r[3], float radius, float height, int slices, int stacks, struct Color c);
void drawSphere(struct Vector3f v1, float radius, int slices, int stacks, struct Color);

struct Particle createParticle(struct Vector3f pos, struct Vector3f vel, struct Vector3f col, float lifetime);
void updateParticle(struct Particle p, float g);
void drawParticle(struct Particle p);
void drawParticles(struct Particle p[], int n_p, float g);

#endif
