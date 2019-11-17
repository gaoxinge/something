#include <GL/glut.h>

void display() {
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glutFlush();
    //glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA)
    //glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(250, 250); 
    glutInitWindowPosition(100, 100);
    glutCreateWindow("My first OpenGL Program");
    glutDisplayFunc(display);
    glutMainLoop();    
    return 0;
}