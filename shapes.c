#include "shapes.h"
#include <GL/freeglut.h>
#include <stdio.h>

Vector3f createVector3f(float x, float y, float z){
    Vector3f v = {x, y, z};
    return v;
}

int vector3fIsEmpty(Vector3f v){
    if (v.x != 0 || v.y != 0 || v.z != 0)
        return 0;
    return 1;
}

void drawBox(Vector3f v1, Vector3f v2, Color c){
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
void drawPyramid(Vector3f v1, Vector3f v2, Color c) {
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
void drawPrism(Vector3f v1, Vector3f v2, Color c) {
    // Draw base
    Vector3f v = {v2.x, v1.y, v2.z};
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
void drawCylinder(Vector3f v1, Vector3f r, float radius, float height, int slices, int stacks, Color c) {
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
void drawCone(Vector3f v1, Vector3f r, float radius, float height, int slices, int stacks, Color c){
    glColor3f(c.r, c.g, c.b);
    glPushMatrix();
    glTranslatef(v1.x, v1.y, v1.z);
    glRotatef(r.x, 1, 0, 0);
    glRotatef(r.y, 0, 1, 0);
    glRotatef(r.z, 0, 0, 1);
    
    glutSolidCone(radius, height, slices, stacks);
    glPopMatrix();
}
void drawSphere(Vector3f v1, float radius, int slices, int stacks, Color c){
    glColor3f(c.r, c.g, c.b);
    glPushMatrix();
    glTranslatef(v1.x, v1.y, v1.z);
    glutSolidSphere(radius, slices, stacks);
    glPopMatrix();
}