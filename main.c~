#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>



static void on_display(void);

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);   
    glutInitWindowPosition(150,150);
    glutInitWindowSize(600,600);
    glutCreateWindow("Lavirint");
    glutDisplayFunc(on_display);
    glClearColor(0.68,0.98,0.68,0);

    glutMainLoop();

    return 0;
}

static void on_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}


