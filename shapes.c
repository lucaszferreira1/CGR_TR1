#include "shapes.h"
#include <GL/freeglut.h>

struct Vector3f createVector3f(float x, float y, float z){
    struct Vector3f v = {x, y, z};
    return v;
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
void drawCylinder(struct Vector3f v1, float radius, float height, int slices, int stacks, struct Color c) {
    glColor3f(c.r, c.g, c.b);
    glPushMatrix();
    glTranslatef(v1.x, v1.y, v1.z);
    glRotatef(270.0, 1.0, 0.0, 0.0);
    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, radius, radius, height, slices, stacks);
    gluDeleteQuadric(quad);
    glPopMatrix();
}
void drawCone(struct Vector3f v1, float radius, float height, int slices, int stacks, struct Color c){
    glColor3f(c.r, c.g, c.b);
    glPushMatrix();
    glTranslatef(v1.x, v1.y, v1.z);
    glRotatef(270.0, 1.0, 0.0, 0.0);
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