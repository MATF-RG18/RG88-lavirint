#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

static int animation_ongoing=0;
static int animation_parameter=0;
float posX=0.0;
float posY=0.0;
float posZ=0.0;

static void draw_ball();
static void on_display(void);
static void on_reshape(int height,int width);
static void on_keyboard(unsigned char,int x, int y);

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DOUBLE);   
    glutInitWindowPosition(150,150);
    glutInitWindowSize(600,600);
    glutCreateWindow("Lavirint");
   
    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);
    
    glClearColor(0.68,0.98,0.68,0);

    glEnable(GL_DEPTH_TEST);

    
    glutMainLoop();

    return 0;
}


static void on_reshape(int width,int height){

glViewport(0,0,width,height);

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(30,(float)width/height,1,25);


}

static void on_keyboard(unsigned char key, int x, int y){

switch(key){
case 27:
exit(0);
break;
case 'w':
case 'W':
posY+=0.1;
break;
case 'a':
case 'A':
posX-=0.1;
break;
case 'd':
case 'D':
posX+=0.1;
break;
case 's':
case 'S':
posY-=0.1;
break;
case 'r':
case 'R':
posZ+=0.1;
break;
case 'f':
case 'F':
posZ-=0.1;
break;

}
glutPostRedisplay();
}

static void on_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5,0,0,0,0,1,0);


    //Crtanje lopte i postavljanje svetla

    GLfloat light_position[]={1,1,1.0,0}; 
    GLfloat light_ambient[]={0.0,0.0,0.0,1};
    GLfloat light_diffuse[]={0.7,0.7,0.7,1};
    GLfloat light_specular[]={0.9,0.9,0.9,1};
	
    

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION,light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT,light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR,light_specular);


    GLfloat ambient_coeffs[]={1,0.1,0,0};
    GLfloat diffuse_coeffs[]={1,0.3,0,0};
    GLfloat specular_coeffs[]={1,1,1,1};
    GLfloat shininess=30;

    glMaterialf(GL_FRONT, GL_SHININESS,shininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT,ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR,specular_coeffs);


    glPushMatrix();
    draw_ball();
    glPopMatrix();
    glutSwapBuffers();
}


static void draw_ball(){

glPushMatrix();
glColor3f(1,1,0);
glTranslatef(posX,posY,posZ);
glutSolidSphere(0.2,40,40);
glPopMatrix();


}

