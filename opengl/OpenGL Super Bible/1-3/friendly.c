#include <GL/glut.h>

float f(float x) {
    return (x - 125.0f) / 125.0f;
}

void renderScene() {
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 1.0f);
    glRectf(f(100.0f), f(150.0f), f(150.0f), f(100.0f));
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
    glutInitWindowSize(250, 250); 
    glutInitWindowPosition(100, 100);
    glutCreateWindow("My second OpenGL Program");
    glutDisplayFunc(renderScene);
    glutMainLoop();
    return 0;
}