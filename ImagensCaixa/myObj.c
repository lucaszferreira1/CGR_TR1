#include <GL/glut.h>
#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" // Include the stb_image library

GLuint textureIDs[6]; // Texture IDs for the loaded images
float angleX = 0.0f; // Initial rotation angle around x-axis
float angleY = 0.0f; // Initial rotation angle around y-axis

void loadTextures(const char *filenames[], int numTextures) {
    for (int i = 0; i < numTextures; ++i) {
        int width, height, channels;
        unsigned char *image = stbi_load(filenames[i], &width, &height, &channels, STBI_rgb);

        if (!image) {
            printf("Failed to load texture: %s\n", filenames[i]);
            continue;
        }

        glGenTextures(1, &textureIDs[i]);
        glBindTexture(GL_TEXTURE_2D, textureIDs[i]);

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Load image data into texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

        // Free image data
        stbi_image_free(image);
    }
}

void drawBox() {
    glEnable(GL_TEXTURE_2D);

    // Front face
    glBindTexture(GL_TEXTURE_2D, textureIDs[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.75f, -0.25f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.75f, -0.25f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.75f, 0.25f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.75f, 0.25f, 0.5f);
    glEnd();

    // Back face
    glBindTexture(GL_TEXTURE_2D, textureIDs[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.75f, -0.25f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.75f, 0.25f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.75f, 0.25f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.75f, -0.25f, -0.5f);
    glEnd();

    // Top face
    glBindTexture(GL_TEXTURE_2D, textureIDs[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.75f, 0.25f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.75f, 0.25f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.75f, 0.25f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.75f, 0.25f, -0.5f);
    glEnd();

    // Bottom face
    glBindTexture(GL_TEXTURE_2D, textureIDs[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.75f, -0.25f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.75f, -0.25f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.75f, -0.25f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.75f, -0.25f, 0.5f);
    glEnd();

    // Right face
    glBindTexture(GL_TEXTURE_2D, textureIDs[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.75f, -0.25f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.75f, 0.25f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.75f, 0.25f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.75f, -0.25f, 0.5f);
    glEnd();

    // Left face
    glBindTexture(GL_TEXTURE_2D, textureIDs[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.75f, -0.25f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.75f, -0.25f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.75f, 0.25f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.75f, 0.25f, -0.5f);
    glEnd();

    glDisable(GL_TEXTURE_2D);

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(angleX, 1.0f, 0.0f, 0.0f); // Rotate around x-axis
    glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotate around y-axis
    // Draw the box
    drawBox();

    glutSwapBuffers();
}

void rotateBox(int value) {
    angleX += 1.0f; // Increment rotation angle around x-axis
    if (angleX >= 360.0f)
        angleX -= 360.0f; // Keep angle within [0, 360] degrees

    angleY += 1.0f; // Increment rotation angle around y-axis
    if (angleY >= 360.0f)
        angleY -= 360.0f; // Keep angle within [0, 360] degrees

    glutPostRedisplay(); // Request redraw
    glutTimerFunc(16, rotateBox, 0); // Call the function again after 16 milliseconds (about 60 FPS)
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Load textures
    const char *filenames[] = {"LadoForm.png", "LadoForm.png", "TopoForm.jpg", "BaixoForm.png", "Lado1Form.png", "Lado1Form.png"};
    loadTextures(filenames, 6);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Texture Mapping");
    glutDisplayFunc(display);

    init();
    glutTimerFunc(16, rotateBox, 0);

    glutMainLoop();
    return 0;
}
