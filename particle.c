#include "particle.h"
#include "shapes.h"
#include <GL/freeglut.h>
#include <stdio.h>

struct Particle createParticle(struct Vector3f pos, struct Vector3f vel, struct Color col, float lifetime){
    struct Particle p;
    p.pos = pos;
    p.vel = vel;
    p.col = col;
    p.lifetime = lifetime;
    return p;
}
void updateParticle(struct Particle p, float g){
    p.pos.y -= g;
    p.pos.x += p.vel.x;
    p.pos.y += p.vel.y;
    p.pos.z += p.vel.z;
    p.lifetime--;
}
void drawParticle(struct Particle p){
    glColor3f(p.col.r, p.col.g, p.col.b);
    glBegin(GL_POINT);
    glVertex3f(p.pos.x, p.pos.y, p.pos.z);
    glEnd();
}
void drawParticles(struct Particle p[], int n_p, float g){
    for (int i=0;i<n_p;i++){
        glEnable(GL_BLEND);
        updateParticle(p[i], g);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        drawParticle(p[i]);
        glDisable(GL_BLEND);
    }
}