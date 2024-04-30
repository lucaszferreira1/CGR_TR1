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
    Color randomColor = {0.0, 0.0, 0.0, 0.0};
    int col = (int)((col2.r - col1.r) * 256.0);
    if (!col) randomColor.r = col2.r;
    else randomColor.r = (rand() % col) / 256.0 + col1.r;
    col = (int)((col2.g - col1.g) * 256.0);
    if (!col) randomColor.g = col2.g;
    else randomColor.g = (rand() % col) / 256.0 + col1.g;
    col = (int)((col2.b - col1.b) * 256.0);
    if (!col) randomColor.b = col2.b;
    else randomColor.b = (rand() % col) / 256.0 + col1.b;
    return randomColor;
}
Vector3f getRandomPointInSphere(Vector3f pos, float radius) {
    Vector3f randomPoint;
    float r = ((float)rand() / RAND_MAX) * radius; // Random radius within the sphere
    float theta = ((float)rand() / RAND_MAX) * 2 * PI; // Random angle theta (0 to 2*pi)
    float phi = ((float)rand() / RAND_MAX) * PI; // Random angle phi (0 to pi)

    // Convert spherical coordinates to Cartesian coordinates
    randomPoint.x = pos.x + r * sin(phi) * cos(theta);
    randomPoint.y = pos.y + r * sin(phi) * sin(theta);
    randomPoint.z = pos.z + r * cos(phi);

    return randomPoint;
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
    glVertex3f(p.pos.x, p.pos.y, p.pos.z);
}
void drawParticles(Particle p[], int n_p, float g){
    glPointSize(p[0].size);
    glBegin(GL_POINTS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    for (int i=0;i<n_p;i++){
        if (p[i].lifetime > 0){
            updateParticle(&p[i], g);
            drawParticle(p[i]);
        }
    }
    glDisable(GL_BLEND);
    glEnd();
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
Particle* generateParticles(int n, int vel_amp, Vector3f pos, Color col1, Color col2, int lifetime, float size, float deltaTime){
    Particle* particles = (Particle*)malloc(n * sizeof(Particle));
    if (particles == NULL){
        printf("Error allocating memory : generateParticles()");
        exit(1); 
    }
    float velocity;
    Vector3f dir;
    for (int i = 0; i < n; i++){
        Particle temp;
        temp.pos = pos;
        temp.col = getRandomColor(col1, col2);
        dir.x = rand() % 360;
        dir.y = rand() % 360;
        velocity = (float)(rand() % vel_amp) / 5000.0;
        temp.vel.x = velocity * sin(radians(dir.y)) * deltaTime;
        temp.vel.y = velocity * cos(radians(dir.y)) * sin(radians(dir.x)) * deltaTime;
        temp.vel.z = velocity * cos(radians(dir.y)) * cos(radians(dir.x)) * deltaTime;
        temp.lifetime = rand() % lifetime;
        temp.size = size;
        particles[i] = temp;
    }

    return particles;
}

Particle* createImpostors(Particle* particles, int N_P, int nImp){
    Particle* impostors = (Particle*)malloc(N_P * sizeof(Particle));
    for (int i=0;i<(N_P / nImp); i++){
        Particle temp;
        Vector3f avgPos = {0.0, 0.0, 0.0};
        Vector3f avgVel = {0.0, 0.0, 0.0};
        Color clrAvg = {0.0, 0.0, 0.0};
        int avgLifetime = 0;
        for (int j=0;j<nImp;j++){
            avgPos.x += particles[i * nImp + j].pos.x;
            avgPos.y += particles[i * nImp + j].pos.y;
            avgPos.z += particles[i * nImp + j].pos.z;

            avgVel.x += particles[i * nImp + j].vel.x;
            avgVel.y += particles[i * nImp + j].vel.y;
            avgVel.z += particles[i * nImp + j].vel.z;

            clrAvg.r += particles[i * nImp + j].col.r;
            clrAvg.g += particles[i * nImp + j].col.g;
            clrAvg.b += particles[i * nImp + j].col.b;
            avgLifetime += particles[i * nImp + j].lifetime;
        }

        avgPos.x /= nImp;
        avgPos.y /= nImp;
        avgPos.z /= nImp;
        
        avgVel.x /= nImp;
        avgVel.y /= nImp;
        avgVel.z /= nImp;
        
        clrAvg.r /= nImp;
        clrAvg.g /= nImp;
        clrAvg.b /= nImp;
        avgLifetime /= nImp;
        
        temp.pos = avgPos;
        temp.vel = avgVel;
        temp.col = clrAvg;
        temp.size = nImp / 2;
        temp.lifetime = avgLifetime;
        impostors[i] = temp;
    }
    return impostors;
}

void updateImpostors(Particle* particles, Particle* impostors, int N_P, int nImp){
    for (int i=0;i<(N_P / nImp); i++){
        Particle temp;
        Vector3f avgPos = {0.0, 0.0, 0.0};
        Vector3f avgVel = {0.0, 0.0, 0.0};
        Color clrAvg = {0.0, 0.0, 0.0};
        int avgLifetime = 0;
        for (int j=0;j<nImp;j++){
            avgPos.x += particles[i * nImp + j].pos.x;
            avgPos.y += particles[i * nImp + j].pos.y;
            avgPos.z += particles[i * nImp + j].pos.z;

            avgVel.x += particles[i * nImp + j].vel.x;
            avgVel.y += particles[i * nImp + j].vel.y;
            avgVel.z += particles[i * nImp + j].vel.z;

            clrAvg.r += particles[i * nImp + j].col.r;
            clrAvg.g += particles[i * nImp + j].col.g;
            clrAvg.b += particles[i * nImp + j].col.b;
            avgLifetime += particles[i * nImp + j].lifetime;
        }

        avgPos.x /= nImp;
        avgPos.y /= nImp;
        avgPos.z /= nImp;
        
        avgVel.x /= nImp;
        avgVel.y /= nImp;
        avgVel.z /= nImp;
        
        clrAvg.r /= nImp;
        clrAvg.g /= nImp;
        clrAvg.b /= nImp;
        avgLifetime /= nImp;
        
        temp.pos = avgPos;
        temp.vel = avgVel;
        temp.col = clrAvg;
        temp.size = nImp / 2;
        temp.lifetime = avgLifetime;
        impostors[i] = temp;
    }
}