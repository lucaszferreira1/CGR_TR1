#include "shapes.h"
#include <GL/glut.h>
#include <GL/glu.h>

// gcc ex_snowman.c shapes.c -o snowman -lGL -lGLU -lglut
// ./snowman

float center = 8;

struct Color color_white = {1.0, 1.0, 1.0};
struct Color color_black = {0.0, 0.0, 0.0};
struct Color color_orange = {1.0, 0.344, 0.0};
struct Color color_red = {1.0, 0.0, 0.0};
struct Color color_sky = {0.675, 0.843, 0.898};

void drawHead(float height, float radius){
    // Head
    struct Vector3f v = {0, height, 0};
    drawSphere(v, radius, 30, 30, color_white);

    // Eyes
    v = createVector3f(-1, height+0.5, radius-0.25);
    drawSphere(v, 0.2, 15, 15, color_black);
    v = createVector3f(1, height+0.5, radius-0.25);
    drawSphere(v, 0.2, 15, 15, color_black);

    // Nose
    v = createVector3f(0, height, radius);
    float r[] = {360, 0, 0};
    drawCone(v, r, 0.5, 2, 15, 15, color_orange);
}
void drawBody(float height, float radius){
    // Top Body
    struct Vector3f v = {0, height, 0};
    drawSphere(v, radius, 30, 30, color_white);
    // Bottom Body
    v.y = height * 8;
    drawSphere(v, radius*1.2, 30, 30, color_white);

    // Buttons
    v = createVector3f(0, height+2, radius);
    drawSphere(v, 0.2, 15, 15, color_black);
    v = createVector3f(0, height+1, radius);
    drawSphere(v, 0.2, 15, 15, color_black);
    v = createVector3f(0, height, radius);
    drawSphere(v, 0.2, 15, 15, color_black);
}
void drawArms(float x, float height, float radius, float length){
    struct Vector3f v = {x, height, 0};
    float r[3] = {0.0, 90.0, 0.0};
    drawCylinder(v, r, radius, length, 15, 15, color_black);

    v = createVector3f(-x, height, 0);
    r[1] = -90;
    drawCylinder(v, r, radius, length, 15, 15, color_black);
}
void drawScarf(float height, float radius, float length){
    struct Vector3f v = {0, height, 0};
    float r[] = {0, 0, 0};
    drawCylinder(v, r, radius, length, 15, 15, color_red);
}
void display() {
    float head_rad = 2.5;
    float head_hei = head_rad * 2;

    float body_rad = head_rad / 3 * 4;
    float body_hei = (head_hei - head_rad) - body_rad;

    float arms_height = body_hei - body_hei / 2;
    float arms_x = body_rad * 0.8;

    float scarf_hei = head_hei + body_hei * 2;
    float scarf_rad = 2.5;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glLoadIdentity();
    gluLookAt((center*2), (center*2), (center*2), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Set the camera position and orientation

    drawHead(head_hei, head_rad);
    drawBody(body_hei, body_rad);
    drawArms(arms_x, arms_height, 0.2, 5);
    drawScarf(scarf_hei, scarf_rad, 1);

    glFlush();
    glutSwapBuffers(); // Use double buffering to avoid flickering
}


void init() {
    glClearColor(color_sky.r, color_sky.g, color_sky.b, 0.0); // Set background color to black
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
    glutCreateWindow("3D Snowman"); // Create a window with the given title

    init(); // Initialize OpenGL parameters
    glutDisplayFunc(display); // Set the display callback function

    glutMainLoop(); // Enter the GLUT event processing loop

    return 0;
}
