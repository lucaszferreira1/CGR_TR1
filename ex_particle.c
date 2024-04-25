#include "shapes.h"
#include "particle.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <unistd.h>
#define CENTER 8.0
#define G 0.0003
#define N_P 2500

// gcc ex_particle.c shapes.c particle.c -o particle -lGL -lGLU -lglut -lm
// ./particle

Color color_sky = {0.675, 0.843, 0.898, 0.0};
Color color_red = {1.0, 0.0, 0.0, 0.0};
int gen = 1;
Particle *particles;

void initParticles(){
    particles = generateParticles(N_P, 10, 1, createVector3f(0.0, 0.0, 0.0), color_red, color_red, 10000, 1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glLoadIdentity();
    gluLookAt((CENTER*2), (CENTER*2), (CENTER*2), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Set the camera position and orientation
    if (gen){
        initParticles();
        gen = 0;
    }

    glBegin(GL_POINTS);
    drawParticles(particles, N_P, G);
    glEnd();

    glutSwapBuffers(); // Use double buffering to avoid flickering
    // usleep(1000);
}


void init() {
    glClearColor(color_sky.r, color_sky.g, color_sky.b, 0.0); // Set background color to black
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

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500); // Set window size
    glutInitWindowPosition(100, 100); // Set window position
    glutCreateWindow("Particle"); // Create a window with the given title

    init(); // Initialize OpenGL parameters
    glutIdleFunc(display);
    glutDisplayFunc(display); // Set the display callback function
    glutMainLoop(); // Enter the GLUT event processing loop

    return 0;
}
