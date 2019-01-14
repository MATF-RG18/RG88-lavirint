#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>


#define TIMER_ID 0
#define TIMER_INTERVAL 20

static int animation_ongoing=1;
static int animation_parameter=0;
float posX=0.0;
float posY=0.0;
float posZ=0.0;

float wall1X=-2;
float wall2X=0.8;

static float t;

static void draw_ball();
static void draw_wall(float t);
static void draw_labyrinth();
static void on_display(void);
static void on_reshape(int height,int width);
static void on_keyboard(unsigned char,int x, int y);
static void on_timer(int value);

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DOUBLE);   
        glutInitWindowPosition(150,150);
        glutInitWindowSize(1000,1000);
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

static void on_timer(int value){

	if(value!=TIMER_ID)
		return;
	
	//Pomeranje zidova:
	
	if(wall1X<0.8){
	wall1X+=0.01;
	}

	if(wall2X>-2){
	wall2X-=0.01;
	}

		

	glutPostRedisplay();

	glutTimerFunc(TIMER_INTERVAL,on_timer,TIMER_ID);

}

static void on_keyboard(unsigned char key, int x, int y){
//Podesavamo da se kuglica krece na w,a,s,d,r i f 
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
	gluLookAt(0,-4,17,0,0,0,0,1,0);


        //Postavljamo boju i svetlo 

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


        GLfloat ambient_coeffs_ball[]={1,0.1,0,0};
        GLfloat diffuse_coeffs_ball[]={1,0.3,0,0};
        GLfloat specular_coeffs_ball[]={1,1,1,0};
        GLfloat shininess_ball=30;

        glMaterialf(GL_FRONT, GL_SHININESS,shininess_ball);
        glMaterialfv(GL_FRONT, GL_AMBIENT,ambient_coeffs_ball);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,diffuse_coeffs_ball);
        glMaterialfv(GL_FRONT, GL_SPECULAR,specular_coeffs_ball);

        //crtamo lopticu
	t=0.03;
        glPushMatrix();
	draw_ball();
        glPopMatrix();


	//Postavljamo boju lavirinta

	GLfloat ambient_coeffs_l[]={0.3,0.3,1,0};
        GLfloat diffuse_coeffs_l[]={0.3,0.3,1,0};
        GLfloat specular_coeffs_l[]={0.3,0.5,0.7,0};
        GLfloat shininess_l=30;

        glMaterialf(GL_FRONT, GL_SHININESS,shininess_l);
        glMaterialfv(GL_FRONT, GL_AMBIENT,ambient_coeffs_l);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,diffuse_coeffs_l);
        glMaterialfv(GL_FRONT, GL_SPECULAR,specular_coeffs_l);




	//crtamo zidove lavirinta
	glPushMatrix();
	glTranslatef(-2,2,0.3);
	glScalef(3.2,t,2);
	draw_wall(0.03);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.5,2,0.3);
	glScalef(3.2,t,2);
	draw_wall(0.03);
	glPopMatrix();

	
	glPushMatrix();
	glRotatef(90,0,0,1);
	glTranslatef(-2,2,0.3);
	glScalef(4,t,2);
	draw_wall(0.03);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2,-2,0.3);
	glScalef(3.2,t,2);
	draw_wall(0.03);
	glPopMatrix();


	glPushMatrix();
	glRotatef(-90,0,0,1);
	glTranslatef(-2,4.7,0.3);
	glScalef(4,t,2);
	draw_wall(0.03);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5,-2,0.3);
	glScalef(3.2,t,2);
	draw_wall(0.03);
	glPopMatrix();
	//Unutrasnjost lavirinta:
	glutTimerFunc(TIMER_INTERVAL,on_timer,TIMER_ID);
	draw_labyrinth();


	glutSwapBuffers();
	
}

//Funkcija za crtanje loptice
static void draw_ball(){

	glPushMatrix();
	glColor3f(1,1,0);
	glTranslatef(posX,posY,posZ);
	glutSolidSphere(0.1,40,40);
	glPopMatrix();

}
//Funkcija za crtanje zidova lavirinta 
//Kod napisan uz pomoc: https://stackoverflow.com/questions/28547173/creating-a-3d-room-in-opengl-c

static void draw_wall(float t){

	glPushMatrix();
	glTranslatef(0.5,0.5*t,1);
	glutSolidCube(1.0);
	glPopMatrix();

}

static void draw_labyrinth(){

	glPushMatrix();
	glTranslatef(-2,-1.5,0);
	glScalef(5.5,t,2);
	draw_wall(0.03);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.6,-1,0);
	glScalef(3.2,t,2);
	draw_wall(0.03);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2,-1,0);
	glScalef(3.2,t,2);
	draw_wall(0.03);
	glPopMatrix();
	//Crtamo pokretne zidove
	glPushMatrix();
	glTranslatef(wall1X,-0.5,0);
	glScalef(4,t,2);
	draw_wall(0.03);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(wall2X,0,0);
	glScalef(4,t,2);
	draw_wall(0.03);
	glPopMatrix();
	
}
