#include "shapes.h"
#include "particle.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#define N_BIRDS 100
#define CENTER 8.0
#define G 0.0003

// gcc ex_flockbirds.c shapes.c particle.c -o birds -lGL -lGLU -lglut -lm
// ./birds

float previousTime = 0.0f;
float deltaTime = 0.0f;

int gen = 1;
Color color_sky = {0.675, 0.843, 0.898, 0.0};

struct Bird{
    int size;
    float x, y, vx, vy, minSeparation, maxSpeed, maxCohesion, radius;
    Color col;
};

typedef struct Bird Bird;

Bird birds[N_BIRDS];

void init_birds(){
    Bird b;
    b.size = 5;
    b.vx = 0;
    b.vy = 0;
    b.minSeparation = 0.5;
    b.maxSpeed = 1;
    b.maxCohesion = 1;
    b.radius = 1;
    b.col = (Color){0.0, 0.0, 0.0, 0.0};
    for (int i=0;i<N_BIRDS;i++){
        b.x = 1;
        b.y = 1;
        birds[i] = b;
    }
}

void drawBirds(){
    glPointSize(birds[0].size);
    glBegin(GL_POINTS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    for (int i=0;i<N_BIRDS;i++){
        glColor4f(birds[i].col.r, birds[i].col.g, birds[i].col.b, birds[i].col.a);
        glVertex2f(birds[i].x, birds[i].y);
    }
    glDisable(GL_BLEND);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glLoadIdentity();
    gluLookAt((CENTER*2), (CENTER*2), (CENTER*2), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Set the camera position and orientation

    if (gen){
        init_birds();
        gen = 0;
    }
    drawBirds();

    glFlush();
    glutSwapBuffers(); // Use double buffering to avoid flickering
}

void update(){
    float currentTime = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = (currentTime - previousTime) / 1000.0f;
    previousTime = currentTime;
    glutPostRedisplay();
    system("clear");
    printf("FPS: %f\n", 1 / deltaTime);
}

void init() {
    srand(time(NULL));
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

void timer(int value) {
    // Update the scene and trigger redrawing
    update();
    glutPostRedisplay();
    glutTimerFunc(15, timer, 0); // Schedule the next update after 16 milliseconds (60 FPS)
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500); // Set window size
    glutInitWindowPosition(100, 100); // Set window position
    glutCreateWindow("Particle"); // Create a window with the given title

    init(); // Initialize OpenGL parameters
    glutIdleFunc(display);
    glutTimerFunc(0, timer, 0); // Start the timer
    glutDisplayFunc(display); // Set the display callback function
    glutMainLoop(); // Enter the GLUT event processing loop

    return 0;
}
