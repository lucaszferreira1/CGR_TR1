#include "shapes.h"
#include <GL/freeglut.h>
#include <stdio.h>

struct Vector3f createVector3f(float x, float y, float z){
    struct Vector3f v = {x, y, z};
    return v;
}
struct Vector4f createVector4f(float r, float x, float y, float z){
    struct Vector4f v;
    v.r = r;
    v.v = createVector3f(x, y, z);
    return v;
}
int vector3fIsEmpty(struct Vector3f v){
    if (v.x != 0 || v.y != 0 || v.z != 0)
        return 0;
    return 1;
}
int vector4fIsEmpty(struct Vector4f v){
    if (v.r != 0 || !vector3fIsEmpty(v.v))
        return 0;
    return 1;
}

void drawBox(struct Vector3f v1, struct Vector3f v2, struct Color c){
    // Set color
    glColor3f(c.r, c.g, c.b);

    // Draw box
    
    // Front face
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v1.z);
    glVertex3f(v1.x, v2.y, v1.z);
    glEnd();

    // Back face
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glVertex3f(v1.x, v1.y, v2.z);
    glVertex3f(v2.x, v1.y, v2.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v1.x, v2.y, v2.z);
    glEnd();

    // Left face
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v1.x, v2.y, v1.z);
    glVertex3f(v1.x, v2.y, v2.z);
    glVertex3f(v1.x, v1.y, v2.z);
    glEnd();

    // Right face
    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);
    glVertex3f(v2.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v2.x, v1.y, v2.z);
    glEnd();

    // Top face
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(v1.x, v2.y, v1.z);
    glVertex3f(v2.x, v2.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v1.x, v2.y, v2.z);
    glEnd();

    // Bottom face
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v1.y, v1.z);
    glVertex3f(v2.x, v1.y, v2.z);
    glVertex3f(v1.x, v1.y, v2.z);
    glEnd();
}
void drawPyramid(struct Vector3f v1, struct Vector3f v2, struct Color c) {
    // Set color
    glColor3f(c.r, c.g, c.b);

    // Draw pyramid
    
    // Front face
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 0, -1);
    glVertex3f((v1.x + v2.x) / 2, v2.y, (v1.z + v2.z) / 2);
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v1.y, v1.z);
    glEnd();

    // Back face
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 0, 1);
    glVertex3f((v1.x + v2.x) / 2, v2.y, (v1.z + v2.z) / 2);
    glVertex3f(v2.x, v1.y, v2.z);
    glVertex3f(v1.x, v1.y, v2.z);
    glEnd();

    // Right face
    glBegin(GL_TRIANGLES);
    glNormal3f(1, 0, 0);
    glVertex3f((v1.x + v2.x) / 2, v2.y, (v1.z + v2.z) / 2);
    glVertex3f(v2.x, v1.y, v1.z);
    glVertex3f(v2.x, v1.y, v2.z);
    glEnd();

    // Left face
    glBegin(GL_TRIANGLES);
    glNormal3f(-1, 0, 0);
    glVertex3f((v1.x + v2.x) / 2, v2.y, (v1.z + v2.z) / 2);
    glVertex3f(v1.x, v1.y, v2.z);
    glVertex3f(v1.x, v1.y, v1.z);
    glEnd();

    // Draw base
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v1.y, v1.z);
    glVertex3f(v2.x, v1.y, v2.z);
    glVertex3f(v1.x, v1.y, v2.z);
    glEnd();
}
void drawPrism(struct Vector3f v1, struct Vector3f v2, struct Color c) {
    // Draw base
    struct Vector3f v = {v2.x, v1.y, v2.z};
    drawBox(v1, v, c);

    // Draw Faces
    glColor3f(c.r, c.g, c.b);
    // Back face
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 0, -1);
    glVertex3f((v1.x + v2.x) / 2, v2.y, v1.z);
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v1.y, v1.z);
    glEnd();

    // Front face
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 0, 1);
    glVertex3f((v1.x + v2.x) / 2, v2.y, v2.z);
    glVertex3f(v1.x, v1.y, v2.z);
    glVertex3f(v2.x, v1.y, v2.z);
    glEnd();

    // // Right Face
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f((v1.x + v2.x) / 2, v2.y, v1.z);
    glVertex3f((v1.x + v2.x) / 2, v2.y, v2.z);
    glVertex3f(v1.x, v1.y, v2.z);
    glEnd();

    // Left Face
    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);
    glVertex3f(v2.x, v1.y, v1.z);
    glVertex3f((v1.x + v2.x) / 2, v2.y, v1.z);
    glVertex3f((v1.x + v2.x) / 2, v2.y, v2.z);
    glVertex3f(v2.x, v1.y, v2.z);
    glEnd();
}
void drawCylinder(struct Vector3f v1, struct Vector3f r, float radius, float height, int slices, int stacks, struct Color c) {
    glColor3f(c.r, c.g, c.b);
    glPushMatrix();
    glTranslatef(v1.x, v1.y, v1.z);
    glRotatef(r.x, 1, 0, 0);
    glRotatef(r.y, 0, 1, 0);
    glRotatef(r.z, 0, 0, 1);

    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, radius, radius, height, slices, stacks);
    gluDeleteQuadric(quad);
    glPopMatrix();
}
void drawCone(struct Vector3f v1, struct Vector3f r, float radius, float height, int slices, int stacks, struct Color c){
    glColor3f(c.r, c.g, c.b);
    glPushMatrix();
    glTranslatef(v1.x, v1.y, v1.z);
    glRotatef(r.x, 1, 0, 0);
    glRotatef(r.y, 0, 1, 0);
    glRotatef(r.z, 0, 0, 1);
    
    glutSolidCone(radius, height, slices, stacks);
    glPopMatrix();
}
void drawSphere(struct Vector3f v1, float radius, int slices, int stacks, struct Color c){
    glColor3f(c.r, c.g, c.b);
    glPushMatrix();
    glTranslatef(v1.x, v1.y, v1.z);
    glutSolidSphere(radius, slices, stacks);
    glPopMatrix();
}

struct Particle createParticle(struct Vector3f pos, struct Vector3f vel, struct Vector3f col, float lifetime){
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
    glColor3f(p.col.x, p.col.y, p.col.z);
    glBegin(GL_POINT);
    glVertex3f(p.pos.x, p.pos.y, p.pos.z);
    glEnd();
}
void drawParticles(struct Particle p[], int n_p, float g){
    for (int i=0;i<n_p;i++){
        updateParticle(p[i], g);
        drawParticle(p[i]);
    }
}
