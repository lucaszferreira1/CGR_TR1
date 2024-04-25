#include "shapes.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>

#define PI 3.1415
#define CENTER 8.0

// gcc ex_robot.c shapes.c -o robot -lGL -lGLU -lglut -lm
// ./robot

Color skin_c = {1.0, 1.0, 1.0, 0.0};
Color joint_c = {0.8, 0.8, 0.8, 0.0};
Vector3f arms_rot[2][2] = {{{45.0, 0.0, 0.0}, {270.0, 0.0, 0.0}}, {{135.0, 0.0, 0.0}, {90.0, 0.0, 0.0}}};
Vector3f legs_rot[2][2] = {{{75.0, 0.0, 0.0}, {75.0, 0.0, 0.0}}, {{105.0, 0.0, 0.0}, {160.0, 0.0, 0.0}}};

float radians(float degree){
    return degree * PI / 180;
}

struct Limb{
    float length, radius;
    Vector3f v, r1, r2;
};
typedef struct Limb Limb;

Limb createLimb(Vector3f v, Vector3f r1, Vector3f r2, float length, float radius){
    Limb l;
    l.v = v;
    l.length = length / 2;
    l.radius = radius;
    l.r1 = r1;
    l.r2 = r2;
    return l;
}
void drawLimb(Limb l){
    Vector3f v = l.v;
    drawCylinder(v, l.r1, l.radius, l.length, 15, 15, skin_c);
    // Top Joint
    drawSphere(v, l.radius-0.01, 15, 15, joint_c);

    // Calculate the position relative to the rotation of the upper arm
    v.x += l.length * sin(radians(l.r1.y));
    v.y -= l.length * cos(radians(l.r1.y)) * sin(radians(l.r1.x));
    v.z += l.length * cos(radians(l.r1.y)) * cos(radians(l.r1.x));

    drawCylinder(v, l.r2, l.radius, l.length, 15, 15, skin_c);
    // Bottom Joint
    drawSphere(v, l.radius-0.01, 15, 15, joint_c);
    
    // Hand / Feet
    v.x += l.length * sin(radians(l.r2.y));
    v.y -= l.length * cos(radians(l.r2.y)) * sin(radians(l.r2.x));
    v.z += l.length * cos(radians(l.r2.y)) * cos(radians(l.r2.x));

    drawSphere(v, l.radius-0.01, 15, 15, joint_c);
}

void drawHead(float height, float radius){
    Vector3f v = {0, height, 0};
    drawSphere(v, radius, 30, 30, skin_c);
}

void drawTorso(float height, float radius, float length){
    Vector3f v = {0, height, 0};
    Vector3f r = {270, 0, 0};
    drawCylinder(v, r, radius, length, 30, 30, skin_c);
    // Bottom Joint
    drawSphere(v, radius-0.01, 15, 15, joint_c);
    // Top Joint
    v.y += length;
    drawSphere(v, radius-0.01, 15, 15, joint_c);
}

void display() {
    float head_rad = (CENTER / 10) * 1.25;
    float head_hei = CENTER;

    float torso_rad = CENTER / 10;
    float torso_hei = CENTER / 8 * 3;
    float torso_len = head_hei / 2;

    float arm_rad = torso_rad / 2;
    float arm_hei = torso_hei + torso_len;
    float arm_len = torso_len;

    float leg_rad = arm_rad;
    float leg_hei = torso_hei - torso_rad;
    float leg_len = arm_len;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glLoadIdentity();
    gluLookAt((CENTER*2), (CENTER*2)+head_hei, (CENTER*2), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Set the camera position and orientation

    drawHead(head_hei, head_rad);
    drawTorso(torso_hei, torso_rad, torso_len);

    Limb rArm = createLimb(createVector3f(-3 * arm_rad, arm_hei, 0), arms_rot[0][0], arms_rot[0][1], arm_len, arm_rad);
    Limb lArm = createLimb(createVector3f(3 * arm_rad, arm_hei, 0), arms_rot[1][0], arms_rot[1][1], arm_len, arm_rad);

    Limb rLeg = createLimb(createVector3f(-leg_rad, leg_hei, 0), legs_rot[0][0], legs_rot[0][1], leg_len, leg_rad);
    Limb lLeg = createLimb(createVector3f(leg_rad, leg_hei, 0), legs_rot[1][0], legs_rot[1][1], leg_len, leg_rad);

    Limb limbs[] = {rArm, lArm, rLeg, lLeg};
    
    for (int i=0;i<4;i++)
        drawLimb(limbs[i]);
    
    glFlush();
    glutSwapBuffers(); // Use double buffering to avoid flickering
}

void update(){
    // Function where the animations will take place
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set background color to black
    glEnable(GL_DEPTH_TEST); // Enable depth testing for proper rendering
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 75.0); // Set the perspective projection
    glMatrixMode(GL_MODELVIEW);

    // Set light parameters
    GLfloat light_position[] = {(CENTER), (CENTER), (CENTER), 8}; // Light position (x, y, z, w)
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

void reshape(int width, int height) {
    // Adjust viewport and projection matrix
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / (float)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void timer(int value) {
    // Update the scene and trigger redrawing
    update();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // Schedule the next update after 16 milliseconds (60 FPS)
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500); // Set window size
    glutInitWindowPosition(100, 100); // Set window position
    glutCreateWindow("3D Robot"); // Create a window with the given title

    init(); // Initialize OpenGL parameters
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0); // Start the timer
    glutDisplayFunc(display); // Set the display callback function
    glutMainLoop(); // Enter the GLUT event processing loop

    return 0;
}
