#include "shapes.h"
#include <GL/glut.h>
#include <GL/glu.h>

// gcc ex_castle.c shapes.c -o castle -lGL -lGLU -lglut
// ./castle

float center = 7.5;
struct Color color_wall = {0.961, 0.627, 0.482};
struct Color color_roof = {0.867, 0.533, 0.388};

void drawFloor(float dis_center){
    struct Vector3f v1;
    struct Vector3f v2;
    // Floor
    struct Color color_white = {1.0, 1.0, 1.0};
    v1 = createVector3f(-dis_center, 0.001, -dis_center);
    v2 = createVector3f(dis_center, 0.001, dis_center);
    drawBox(v1, v2, color_white);

    // Ground
    struct Color color_green = {0.0, 0.2, 0.0};
    v1 = createVector3f(-dis_center*2, 0.0, -dis_center*2);
    v2 = createVector3f(dis_center*2, 0.0, dis_center*2);
    drawBox(v1, v2, color_green);
}

void drawWalls(float dis_center, float thick, float height){
    struct Vector3f v1;
    struct Vector3f v2;

    // Back side
    v1 = createVector3f(-dis_center, 0, -dis_center-thick);
    v2 = createVector3f(dis_center, height, -dis_center+thick);
    drawBox(v1, v2, color_wall);

    // Right side
    v1 = createVector3f(-dis_center-thick, 0, -dis_center);
    v2 = createVector3f(-dis_center+thick, height, dis_center);
    drawBox(v1, v2, color_wall);

    // Left side
    v1 = createVector3f(dis_center-thick, 0, -dis_center);
    v2 = createVector3f(dis_center+thick, height, dis_center);
    drawBox(v1, v2, color_wall);
    
    // Front face
    v1 = createVector3f(-dis_center, 0, dis_center-thick);
    v2 = createVector3f(dis_center, height, dis_center+thick);
    drawBox(v1, v2, color_wall);

    float prism_hei = height * 1.15;

    // Back wall roof
    v1 = createVector3f(-dis_center-thick, height, -dis_center);
    v2 = createVector3f(-dis_center+thick, prism_hei, dis_center);
    glPushMatrix();
    glRotatef(-90, 0, 1, 0);
    drawPrism(v1, v2, color_roof);
    glPopMatrix();

    // Right wall roof
    drawPrism(v1, v2, color_roof);

    // Left wall roof
    v1 = createVector3f(dis_center-thick, height, -dis_center);
    v2 = createVector3f(dis_center+thick, prism_hei, dis_center);
    drawPrism(v1, v2, color_roof);
    
    // Front wall roof
    glPushMatrix();
    glRotatef(-90, 0, 1, 0);
    drawPrism(v1, v2, color_roof);
    glPopMatrix();
}

void drawTowers(float dis_center, float radius){
    struct Vector3f v;
    struct Vector3f r = {270, 0, 0};
    for (int i=-1;i<2;i+=2){
        for(int j=-1;j<2;j+=2){
            // Draw cylinders
            v = createVector3f(dis_center*i, 0, dis_center*j);
            drawCylinder(v, r, radius, dis_center, 20, 20, color_wall);

            // Draw roofs
            v = createVector3f(dis_center*i, dis_center, dis_center*j);
            drawCone(v, r, radius + (radius / 15), 2, 20, 20, color_roof);
        }
    }
}

void drawCenterTower(float width, float height){
    struct Vector3f v1;
    struct Vector3f v2;

    // Draw the building
    v1 = createVector3f(-width, 0, -width);
    v2 = createVector3f(width, height, width);
    drawBox(v1, v2, color_wall);

    float roof_wid = width + width / 6;
    float roof_hei = height + height / 4;
    // Draw the roof
    v1 = createVector3f(-roof_wid, height, -roof_wid);
    v2 = createVector3f(roof_wid, roof_hei, roof_wid);
    drawPyramid(v1, v2, color_roof);
}

void drawGate(float dis_center, float thick, float width, float height){
    struct Vector3f v1;
    struct Vector3f v2;

    // Draw gate building
    v1 = createVector3f(dis_center-thick, 0, -width);
    v2 = createVector3f(dis_center+thick, height, width);
    drawBox(v1, v2, color_wall);
    
    float prism_hei = height + (height / 5);
    // Draw gate roof
    v1 = createVector3f(dis_center-thick*1.1, height, -width);
    v2 = createVector3f(dis_center+thick*1.1, height*1.2, width);
    drawPrism(v1, v2, color_roof);

    // Draw gate
    float gate_wid = width / 2;
    float gate_hei = height / 1.5;
    v1 = createVector3f(dis_center-thick-0.01, 0, -gate_wid);
    v2 = createVector3f(dis_center+thick+0.01, gate_hei, gate_wid);
    drawBox(v1, v2, color_roof);
}

void display() {
    
    float wall_hei = 5;
    float wall_thi = 0.5;

    float towers_rad = 1.5;

    float mtower_wid = 1.3;
    float mtower_hei = 7.5;

    float gate_wid = 3;
    float gate_hei = 5;
    float gate_thi = 1;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glLoadIdentity();
    gluLookAt((center*2)+5, (center*2)+5, (center*2)+5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Set the camera position and orientation

    drawFloor(center);

    drawWalls(center, wall_thi, wall_hei);

    drawTowers(center, towers_rad);

    drawCenterTower(mtower_wid, mtower_hei);

    drawGate(center, gate_thi, gate_wid, gate_hei);

    

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
    glutCreateWindow("3D Castle"); // Create a window with the given title

    init(); // Initialize OpenGL parameters
    glutDisplayFunc(display); // Set the display callback function

    glutMainLoop(); // Enter the GLUT event processing loop

    return 0;
}
