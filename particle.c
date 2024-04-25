#include "particle.h"
#include "shapes.h"
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define PI 3.1415

float radians(float degree){
    return degree * PI / 180;
}
Color getRandomColor(Color col1, Color col2){
    Color randomColor;
    int col = (int)((col2.r - col1.r) * 256);
    if (!col) col = 1;
    randomColor.r = (rand() % col) / 256 + col1.r;
    col = (int)(col2.g - col1.g) * 256;
    if (!col) col = 1;
    randomColor.g = (rand() % col) / 256 + col1.g;
    col = (int)(col2.b - col1.b) * 256;
    if (!col) col = 1;
    randomColor.b = (rand() % col) / 256 + col1.b;
    return randomColor;
}
Particle createParticle(Vector3f pos, Vector3f vel, Color col, int lifetime, float size){
    Particle p;
    p.pos = pos;
    p.vel = vel;
    p.col = col;
    p.lifetime = lifetime;
    p.size = size;
    return p;
}
void updateParticle(Particle *p, float g){
    p->pos.y -= g;
    p->pos.x += p->vel.x;
    p->pos.y += p->vel.y;
    p->pos.z += p->vel.z;
    p->lifetime--;
}
void drawParticle(Particle p){
    glColor4f(p.col.r, p.col.g, p.col.b, p.col.a);
    glPointSize(p.size);
    glVertex3f(p.pos.x, p.pos.y, p.pos.z);
}
void drawParticles(Particle p[], int n_p, float g){
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    for (int i=0;i<n_p;i++){
        if (p[i].lifetime > 0){
            updateParticle(&p[i], g);
            drawParticle(p[i]);
        }
    }
    glDisable(GL_BLEND);
}
/* Function which returns an array of particles
n : number of particles
vel_amp : amplitude of velocity (if 0 all will have the same velocity)
size_amp : amplitude of size (if 0 all will have the same size)
pos : position of particles
col1 : min color for the range of colors
col2 : max color for the range of colors (if col2 == col1 all will have the same color)
lifetime : lifetime of the particles
size : of the particles
*/
Particle* generateParticles(int n, int vel_amp, int size_amp, Vector3f pos, Color col1, Color col2, int lifetime, float size){
    srand(time(NULL));
    Particle* particles = (Particle*)malloc(n * sizeof(Particle));
    if (particles == NULL){
        printf("Error allocating memory : generateParticles()");
        exit(1); 
    }
    float velocity;
    float size_diff, size_ud;
    Vector3f dir;
    for (int i = 0; i < n; i++){
        Particle temp;
        temp.pos = pos;
        temp.col = getRandomColor(col1, col2);
        dir.x = rand() % 360;
        dir.y = rand() % 360;
        velocity = (float)(rand() % vel_amp) / 5000.0;
        temp.vel.x = velocity * sin(radians(dir.y));
        temp.vel.y = velocity * cos(radians(dir.y)) * sin(radians(dir.x));
        temp.vel.z = velocity * cos(radians(dir.y)) * cos(radians(dir.x));;
        temp.lifetime = rand() % lifetime;
        temp.size = size;
        size_diff = (rand() % size_amp) / 100;
        size_ud = rand() % 2;
        if (size_ud)
            temp.size -= size_diff;
        else
            temp.size += size_diff;
        particles[i] = temp;
    }

    return particles;
}
