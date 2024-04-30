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

Color getRandomColor(Color col1, Color col2);
Vector3f getRandomPointInSphere(Vector3f pos, float radius);
Particle createParticle(Vector3f pos, Vector3f vel, Color col, int lifetime, float size);
void updateParticle(Particle *p, float g);
void drawParticle(Particle p);
void drawParticles(Particle p[], int n_p, float g);
Particle* generateParticles(int n, int vel_amp, Vector3f pos, Color col1, Color col2, int lifetime, float size, float deltaTime);
Particle* createImpostors(Particle* particles, int N_P, int nImp);
void updateImpostors(Particle* particles, Particle* impostors, int N_P, int nImp);

#endif
