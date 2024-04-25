#include "shapes.h"
#ifndef PARTICLE_H
#define PARTICLE_H

struct Particle{
    Vector3f pos, vel;
    Color col;
    float lifetime;
};
typedef Particle Particle;

Particle createParticle(Vector3f pos, Vector3f vel, Vector3f col, float lifetime);
void updateParticle(Particle p, float g);
void drawParticle(Particle p);
void drawParticles(Particle p[], int n_p, float g);

#endif