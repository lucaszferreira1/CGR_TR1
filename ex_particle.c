#include "shapes.h"
#include "particle.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <unistd.h>
#include <time.h>
#define CENTER 8.0
#define G 0.0003
#define N_P 10000

// gcc ex_particle.c shapes.c particle.c -o particle -lGL -lGLU -lglut -lm
// ./particle

float previousTime = 0.0f;
float deltaTime = 0.0f;

Color color_white = {1.0, 1.0, 1.0, 0.0};
Color color_sky = {0.675, 0.843, 0.898, 0.0};
Color color_red = {1.0, 0.0, 0.0, 0.0};
Color color_orange = {1.0, 0.5, 0.0, 0.0};
Color color_blue = {0.183, 0.336, 0.91, 0.5};
Color color_lightblue = {0.2, 0.8, 1.0, 0.5};
int gen = 1;
Particle *particles;
Particle *impostors;

void initExplosionParticles(){
    particles = generateParticles(N_P, 10, createVector3f(0.0, 0.0, 0.0), color_red, color_orange, 10000, 5, deltaTime);
}

void initRainParticles(Vector3f pos, float rad){
    Particle* ps = (Particle*)malloc(N_P * sizeof(Particle));
    for (int i=0;i<N_P;i++){
        Particle temp;
        temp.pos = getRandomPointInSphere(pos, rad);
        temp.lifetime = rand() % 100000;
        temp.col = getRandomColor(color_blue, color_lightblue);
        temp.vel = createVector3f(0.0, -0.001 * deltaTime, 0.0);
        temp.size = 2;
        ps[i] = temp;
    }
    particles = ps;
}

void initFireParticles(Vector3f pos){
    Particle* ps = (Particle*)malloc(N_P * sizeof(Particle));
    for (int i = 0; i < N_P; i++) {
        Particle temp;
        temp.pos = pos;
        temp.lifetime = rand() % 100000;
        temp.col = getRandomColor(color_red, color_orange);
        temp.vel = (Vector3f){(rand() % 2001 - 1000) / 1000000.0f * deltaTime, (rand() % 1000) / 1000000.0f + 0.001f * deltaTime, (rand() % 2001 - 1000) / 1000000.0f * deltaTime};
        temp.size = 2;
        ps[i] = temp;
    }
    particles = ps;
}

void initWaterfallParticles(Vector3f pos, float radius){
    Particle* ps = (Particle*)malloc(N_P * sizeof(Particle));
    for (int i = 0; i < N_P; i++) {
        Particle temp;
        temp.pos = pos;
        temp.pos.x += ((float)rand() / RAND_MAX) * radius - radius;
        temp.pos.z += ((float)rand() / RAND_MAX) * radius - radius;
        temp.lifetime = rand() % 100000;
        temp.col = getRandomColor(color_blue, color_lightblue);
        temp.vel = (Vector3f){0.0, (rand() % 1000) / -1000000.0f * deltaTime, 0.0};
        temp.size = 2;
        ps[i] = temp;
    }
    particles = ps;
}

void useImpostors(int n){
    updateImpostors(particles, impostors, N_P, n);
    for (int i=0;i<N_P;i++)
        updateParticle(&particles[i], G);
}

void createListImpostors(int n){
    Particle* ims = (Particle*)malloc(n * sizeof(Particle));
    ims = createImpostors(particles, N_P, n);
    impostors = ims;
    for (int i=0;i<N_P;i++)
        updateParticle(&particles[i], G);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glLoadIdentity();
    gluLookAt((CENTER*2), (CENTER*2), (CENTER*2), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Set the camera position and orientation
    if (gen){
        // initExplosionParticles();
        // initRainParticles(createVector3f(0.0, 5.0, 0.0), 20);
        initFireParticles(createVector3f(0.0, 0.0, 0.0));
        // initWaterfallParticles(createVector3f(0.0, 0.0, 0.0), 20);
        
        createListImpostors(10);

        gen = 0;
    }

    useImpostors(10);
    drawParticles(impostors, N_P, G);
    // drawParticles(particles, N_P, G);

    glFlush();
    glutSwapBuffers(); // Use double buffering to avoid flickering
}

void update(){
    float currentTime = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = (currentTime - previousTime) / 1000.0f;
    previousTime = currentTime;
    glutPostRedisplay();
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
    glutTimerFunc(16, timer, 0); // Schedule the next update after 16 milliseconds (60 FPS)
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
