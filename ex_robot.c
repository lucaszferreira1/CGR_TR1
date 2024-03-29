#include "shapes.h"
#include <GL/glut.h>
#include <GL/glu.h>

// gcc ex_robot.c shapes.c -o robot -lGL -lGLU -lglut
// ./robot

float center = 7.5;

struct Color skc = {1.0, 1.0, 1.0};

void drawHead(float height, float radius){
    struct Vector3f v = {0, height, 0};
    drawSphere(v, radius, 30, 30, skc);
}

void drawTorso(float height, float radius, float length){
    struct Vector3f v = {0, height, 0};
    struct Vector4f r = {0, 0, 0, 0};
    drawCylinder(v, r, radius, length, 30, 30, skc);
}

void drawArms(float height, float radius, float length){
    struct Vector3f v = {-0.8-radius, height, 0};
    struct Vector4f r = {90.0, createVector3f(1.0, 0.0, 0.0)};
    drawCylinder(v, r, radius, length / 2, 15, 15, skc);

    v = createVector3f(0.8+radius, height, 0);
    drawCylinder(v, r, radius, length / 2, 15, 15, skc);

    v = createVector3f(-0.8-radius, height-length/2, 0);
    drawCylinder(v, r, radius, length / 2, 15, 15, skc);

    v = createVector3f(0.8+radius, height-length/2, 0);
    drawCylinder(v, r, radius, length / 2, 15, 15, skc);
}

void drawLegs(float height, float radius, float length){
    struct Vector3f v = {-radius, height, 0};
    struct Vector4f r = {90.0, createVector3f(1.0, 0.0, 0.0)};
    drawCylinder(v, r, radius, length, 15, 15, skc);

    v = createVector3f(radius, height, 0);
    drawCylinder(v, r, radius, length, 15, 15, skc);

    v = createVector3f(-radius, height-length, 0);
    drawCylinder(v, r, radius, length, 15, 15, skc);

    v = createVector3f(radius, height-length, 0);
    drawCylinder(v, r, radius, length, 15, 15, skc);
}

void drawFeet(){
    // struct Vector3f v1 = {-0.4, -0.2, 0.0};
    // struct Vector3f v2 = {0.4, 0.0, 1.0};
    // drawBox(v1, v2, skc);

    // v1 = createVector3f(-0.5, 0, 0);
    // v2 = createVector3f(-0.5, 0, 1);
    // drawBox(v1, v2, skc);
}

void display() {
    float head_hei = 8;

    float torso_hei = 3;
    float torso_len = 4;

    float arm_hei = torso_hei + torso_len;
    float arm_len = torso_len;

    float leg_hei = torso_hei;
    float leg_len = 2;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glLoadIdentity();
    gluLookAt((center*2), (center*2), (center*2), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Set the camera position and orientation

    drawHead(head_hei, 1.0);
    drawTorso(torso_hei, 0.8, torso_len);
    drawArms(arm_hei, 0.4, arm_len);
    drawLegs(leg_hei, 0.4, leg_len);
    drawFeet();

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