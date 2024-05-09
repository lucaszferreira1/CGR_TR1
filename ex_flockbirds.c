#include <GL/glut.h>
#include <GL/glu.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#define N_BIRDS 20
#define CENTER 8.0
#define G 0.0003

// gcc ex_flockbirds.c -o birds -lGL -lGLU -lglut -lm
// ./birds

float previousTime = 0.0f;
float deltaTime = 0.0f;

struct Color{
    float r, g, b, a;
}; typedef struct Color Color;

struct Bird{
    float x, y, vx, vy;
}; typedef struct Bird Bird;


struct Birds{
    Bird bs[N_BIRDS];
    int size;
    float minSeparation, maxSpeed, perceptionRadius;
    Color col;
};typedef struct Birds Birds;

int gen = 1;
Color color_sky = {0.675, 0.843, 0.898, 0.0};

Birds birds;

float disToBird(Bird *b1, Bird *b2){
    return (float)sqrt((float)pow((b1->x - b2->x), 2) + (float)pow((b1->y - b2->y), 2));
}

void checkBoundarieVio(Bird *b){
    if (b->x >= 20 || b->x <= -20 || b->y <= -20 || b->y >= 20){
        b->x = -10;
        b->y = 10;
    }
    return;
}

void initBirds(){
    Bird b;
    b.vx = 0;
    b.vy = 0;
    birds.size = 5;
    birds.minSeparation = 2;
    birds.maxSpeed = 2;
    birds.perceptionRadius = 50;
    birds.col = (Color){0.0, 0.0, 0.0, 0.0};
    for (int i=0;i<N_BIRDS;i++){
        b.x = (rand() / (float)RAND_MAX) * 20 - 10;
        b.y = (rand() / (float)RAND_MAX) * 20 - 10;
        birds.bs[i] = b;
    }
}

void drawBirds(){
    glPointSize(birds.size);
    glBegin(GL_POINTS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    for (int i=0;i<N_BIRDS;i++){
        glColor4f(birds.col.r, birds.col.g, birds.col.b, birds.col.a);
        glVertex2f(birds.bs[i].x, birds.bs[i].y);
    }
    glDisable(GL_BLEND);
    glEnd();
}

void updateBirds(){
    Bird *b1, *b2;
    float avrgVel[2];
    float avrgPos[2];
    float avrgSep[2];
    int numNeighbors;
    float dist;
    for (int i=0;i<N_BIRDS;i++){
        b1 = &birds.bs[i];
        b1->x += b1->vx;
        b1->y += b1->vy;

        avrgVel[0] = 0.0;
        avrgVel[1] = 0.0;
        avrgPos[0] = 0.0;
        avrgPos[1] = 0.0;
        avrgSep[0] = 0.0;
        avrgSep[1] = 0.0;
        numNeighbors = 0;
        checkBoundarieVio(b1);

        for (int j=0;j<N_BIRDS;j++){
            if (i == j)
                continue;
            dist = disToBird(b1, b2);
            if (dist <= birds.perceptionRadius){
                avrgVel[0] += b2->vx;
                avrgVel[1] += b2->vy;
                avrgPos[0] += b2->x;
                avrgPos[1] += b2->y;
                if (dist <= birds.minSeparation){
                    avrgSep[0] += abs(b1->x - b2->x);
                    avrgSep[0] += abs(b1->y - b2->y);   
                }
                numNeighbors++;
            }
        }
        if (numNeighbors){
            avrgVel[0] /= numNeighbors;
            avrgVel[1] /= numNeighbors;
            avrgPos[0] /= numNeighbors;
            avrgPos[1] /= numNeighbors;
            avrgSep[0] /= numNeighbors;
            avrgSep[1] /= numNeighbors;
        }
        b1->vx += (avrgVel[0] * 0.02) + (avrgPos[0] * 0.01) - (avrgSep[0] * 0.03);
        b1->vy += (avrgVel[1] * 0.02) + (avrgPos[0] * 0.01) - (avrgSep[0] * 0.03);
    }
    drawBirds();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glLoadIdentity();

    if (gen){
        glTranslatef(0.0, 0.0, -20.0);
        glPushMatrix();
        initBirds();
        glPopMatrix();
        gen = 0;
    }

    updateBirds();

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

void init(void) {
    glClearColor(color_sky.r, color_sky.g, color_sky.b, color_sky.a);
    glOrtho (0, 500, 0, 500, -1 ,1);
    glEnable(GL_DEPTH_TEST); // Enable depth testing for proper rendering
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 75.0); // Set the perspective projection
    glMatrixMode(GL_MODELVIEW);
}

void timer(int value) {
    // Update the scene and trigger redrawing
    update();
    glutPostRedisplay();
    glutTimerFunc(15, timer, 0); // Schedule the next update after 16 milliseconds (60 FPS)
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init();
    glutIdleFunc(display);
    glutTimerFunc(0, timer, 0); // Start the timer
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
