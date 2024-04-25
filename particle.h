#ifndef PARTICLE_H
#define PARTICLE_H

#include "shapes.h"

struct Particle{
    Vector3f pos, vel;
    Color col;
    int lifetime;
    float size;
};
typedef struct Particle Particle;

Particle createParticle(Vector3f pos, Vector3f vel, Color col, int lifetime, float size);
void updateParticle(Particle *p, float g);
void drawParticle(Particle p);
void drawParticles(Particle p[], int n_p, float g);
Particle* generateParticles(int n, int vel_amp, int size_amp, Vector3f pos, Color col1, Color col2, int lifetime, float size);

#endif
