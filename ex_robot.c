#include "shapes.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>

#define PI 3.1415

// gcc ex_robot.c shapes.c -o robot -lGL -lGLU -lglut -lm
// ./robot

float center = 8;
struct Color skin_c = {1.0, 1.0, 1.0};
struct Color joint_c = {0.8, 0.8, 0.8};

float radians(float degree){
    return degree * PI / 180;
}

struct Limb{
    float length, radius;
    struct Vector3f v, r1, r2;
};
struct Limb createLimb(struct Vector3f v, float length, float radius){
    struct Limb l;
    l.v = v;
    l.length = length / 2;
    l.radius = radius;
    l.r1 = createVector3f(90.0, 0.0, 0.0);
    l.r2 = createVector3f(90.0, 0.0, 0.0);
    return l;
}
void drawLimb(struct Limb l){
    struct Vector3f v = l.v;
    drawCylinder(v, l.r1, l.radius, l.length, 15, 15, skin_c);
    // Top Joint
    drawSphere(v, l.radius-0.01, 15, 15, joint_c);

    // Calculate the position relative to the rotation of the upper arm

    v.y += cos(radians(l.r1.z)) * l.length - sin(radians(l.r1.x)) * l.length;
    v.x += sin(radians(l.r1.y)) * l.length + sin(radians(l.r1.z)) * l.length;
    // v.z -= sin(radians(l.r1.z)) * l.length;

    drawCylinder(v, l.r2, l.radius, l.length, 15, 15, skin_c);
    // Bottom Joint
    drawSphere(v, l.radius-0.01, 15, 15, joint_c);
    
    // Hand / Feet
    drawSphere(v, l.radius-0.01, 15, 15, joint_c);
}

void drawHead(float height, float radius){
    struct Vector3f v = {0, height, 0};
    drawSphere(v, radius, 30, 30, skin_c);
}

void drawTorso(float height, float radius, float length){
    struct Vector3f v = {0, height, 0};
    struct Vector3f r = {270, 0, 0};
    drawCylinder(v, r, radius, length, 30, 30, skin_c);
    // Bottom Joint
    drawSphere(v, radius-0.01, 15, 15, joint_c);
    // Top Joint
    v.y += length;
    drawSphere(v, radius-0.01, 15, 15, joint_c);
}

void display() {
    float head_rad = (center / 10) * 1.25;
    float head_hei = center;

    float torso_rad = center / 10;
    float torso_hei = center / 8 * 3;
    float torso_len = head_hei / 2;

    float arm_rad = torso_rad / 2;
    float arm_hei = torso_hei + torso_len;
    float arm_len = torso_len;

    float leg_rad = arm_rad;
    float leg_hei = torso_hei - torso_rad;
    float leg_len = arm_len;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glLoadIdentity();
    gluLookAt((center*2), (center*2)+head_hei, (center*2), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Set the camera position and orientation

    drawHead(head_hei, head_rad);
    drawTorso(torso_hei, torso_rad, torso_len);

    struct Limb rArm = createLimb(createVector3f(-3 * arm_rad, arm_hei, 0), arm_len, arm_rad);
    struct Limb lArm = createLimb(createVector3f(3 * arm_rad, arm_hei, 0), arm_len, arm_rad);

    struct Limb rLeg = createLimb(createVector3f(-leg_rad, leg_hei, 0), leg_len, leg_rad);
    struct Limb lLeg = createLimb(createVector3f(leg_rad, leg_hei, 0), leg_len, leg_rad);

    struct Limb limbs[] = {rArm, lArm, rLeg, lLeg};

    for (int i=0;i<4;i++)
        drawLimb(limbs[i]);
    
    glFlush();
    glutSwapBuffers(); // Use double buffering to avoid flickering
}


void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set background color to black
    glEnable(GL_DEPTH_TEST); // Enable depth testing for proper rendering
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 75.0); // Set the perspective projection
    glMatrixMode(GL_MODELVIEW);

    // Set light parameters
    GLfloat light_position[] = {(center), (center), (center), 8}; // Light position (x, y, z, w)
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // Set material properties
    GLfloat material_ambient[] = {0.8, 0.8, 0.8, 1.0}; // Ambient material color (R, G, B, A)
    GLfloat material_diffuse[] = {0.8, 0.8, 0.8, 1.0}; // Diffuse material color (R, G, B, A)
    GLfloat material_specular[] = {1.0, 1.0, 1.0, 1.0}; // Specular material color (R, G, B, A)
    GLfloat material_shininess[] = {100.0}; // Shininess of the material
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material_shininess);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_SHININESS);
    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); // Enable light source 0
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500); // Set window size
    glutInitWindowPosition(100, 100); // Set window position
    glutCreateWindow("3D Robot"); // Create a window with the given title

    init(); // Initialize OpenGL parameters
    glutDisplayFunc(display); // Set the display callback function

    glutMainLoop(); // Enter the GLUT event processing loop

    return 0;
}
