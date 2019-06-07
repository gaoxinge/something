#include <math.h>
#include <GL/glut.h>

#define PI 3.1415926535898

void display() {
    GLint cicle_points = 100000;
    
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    for (GLint i = 0; i < cicle_points; i++) {
        GLfloat angle = 2 * PI * i / cicle_points;
        glVertex2f(cos(angle), sin(angle));
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("hello");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}