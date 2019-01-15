#include <stdlib.h>
#include <GL/glut.h>
#include<math.h>
#define TIMER_INTERVAL 40
#define TIMER_ID 0

static int window_width, window_height;

float posX=1;
float posY=1;
float posZ=1;
float wall1Z=0.3;
int wall_direction=-1;
float x=0;
float t=0;
float z=0;
const static float pi = 3.141592653589793;


static void draw_wall(float t,float x,float z);
static void draw_labyrinth();
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void draw_ball();
static void on_timer(int value);



int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);


    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lavirint");


    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    glClearColor(0.68,0.98,0.68,0);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(2);
   

    glutMainLoop();

    return 0;
}



static void on_timer(int value){

	if(value!=TIMER_ID)
	return;


	if(wall_direction==1){
	wall1Z+=0.0001;
	}
	else
	wall1Z-=0.0001;

	if(wall1Z<-0.3 || wall1Z>0.3){
	wall_direction=-wall_direction;
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

	case 's':
	case 'S':
		posX-=0.1;


	break;
	
	case 'w':
	case 'W':

		posX+=0.1;

	
	break;
	case 'd':
	case 'D':
		posZ+=0.1;
		//lx+=0.1f;
	 
	break;
	case 'A':
	case 'a':
	
	posZ-=0.1;

    
	break;

}


	glutPostRedisplay();
}
static void on_reshape(int width, int height)
{

    window_width = width;
    window_height = height;
}

static void on_display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glViewport(0, 0, window_width, window_height);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    gluPerspective(
           30,
            window_width/(float)window_height,
            1, 25);

    glMatrixMode(GL_MODELVIEW);


    
    glLoadIdentity();
          // gluLookAt(posX + (cos(90)*2), posY + (2*sin(90)), posZ, posX, posY, posZ, 0, 1, 0);

    gluLookAt(6,6,6,0,0,0,0,1,0);

    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslatef(1,1,1);
    glScalef(2,2,2);
    glutWireCube(1);
    glPopMatrix();

    
    glPopMatrix();
    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(10,0,0);
        
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,10,0);
        
        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,10);
    glEnd();


	glutTimerFunc(TIMER_INTERVAL,on_timer,TIMER_ID);
	//Crtamo zidove lavirinta i namestamo boju
	GLfloat light_position[]={2,0,-1,1}; 
	GLfloat ambient_coeffs_l[]={0.3,0.3,1,0};
        GLfloat diffuse_coeffs_l[]={0.3,0.3,1,0};
        GLfloat specular_coeffs_l[]={0.8,0.8,0.3,0};
        GLfloat shininess_l=30;

	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//Crtanje unutrasnjosti lavirinta
	draw_labyrinth();

	glLightfv(GL_LIGHT0, GL_POSITION,light_position);
        glMaterialf(GL_FRONT, GL_SHININESS,shininess_l);
        glMaterialfv(GL_FRONT, GL_AMBIENT,ambient_coeffs_l);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,diffuse_coeffs_l);
        glMaterialfv(GL_FRONT, GL_SPECULAR,specular_coeffs_l);



	//Crtanje zidova koji cine okvir lavirinta
	
	//Izlaz i zidovi pored
	glPushMatrix();
	glRotatef(90,0,0,1);
	x=0.5;
	z=1.0;
	glTranslatef(-0.2,0,0.6);
	draw_wall(0.1,x,z);
	glPopMatrix(); 

	glPushMatrix();
	glRotatef(90,0,0,1);
	x=0.5;
	z=0.5;
	glTranslatef(-0.2,0,-0.75);
	draw_wall(0.1,x,z);
	glPopMatrix(); 


	//ulaz i zidovi pored
	glPushMatrix();
	glRotatef(90,0,0,1);
	x=0.5;
	z=1;
	glTranslatef(-0.2,-2.1,0.6);
	draw_wall(0.1,x,z);
	glPopMatrix(); 

	glPushMatrix();
	glRotatef(90,0,0,1);
	x=0.5;
	z=0.5;
	glTranslatef(-0.2,-2.1,-0.75);
	draw_wall(0.1,x,z);
	glPopMatrix(); 

	//zidove sa strane:

	glPushMatrix();
	glRotatef(90,0,1,0);
	glRotatef(90,0,0,1);
	x=0.5;
	z=2;
	glTranslatef(-0.2,0,0);
	draw_wall(0.1,x,z);
	glPopMatrix(); 

	glPushMatrix();
	glRotatef(90,0,1,0);
	glRotatef(90,0,0,1);
	x=0.5;
	z=2;
	glTranslatef(-0.2,2,0);
	draw_wall(0.1,x,z);
	glPopMatrix(); 
	


	//Pod i svetlo


	GLfloat ambient_coeffs_floor[]={0.3,1,1,0};
        GLfloat diffuse_coeffs_floor[]={0.1,1,1,0};
        GLfloat specular_coeffs_floor[]={0.3,0.8,0.3,1};
        GLfloat shininess_floor=30;

	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


        glMaterialf(GL_FRONT, GL_SHININESS,shininess_floor);
        glMaterialfv(GL_FRONT, GL_AMBIENT,ambient_coeffs_floor);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,diffuse_coeffs_floor);
        glMaterialfv(GL_FRONT, GL_SPECULAR,specular_coeffs_floor);
	glPushMatrix();
	x=2.0;
	t=0.03;
	z=2;	
	glTranslatef(0.5,0,0);
	draw_wall(t,x,z);
	glPopMatrix();

//postavljamo boju za lopticu i crtamo lopticu

	GLfloat ambient_coeffs_ball[]={1,0.1,0,0};
        GLfloat diffuse_coeffs_ball[]={1,0.3,0,0};
        GLfloat specular_coeffs_ball[]={0.6,0.7,0.8,0};
        GLfloat shininess_ball=30;

        glMaterialf(GL_FRONT, GL_SHININESS,shininess_ball);
        glMaterialfv(GL_FRONT, GL_AMBIENT,ambient_coeffs_ball);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,diffuse_coeffs_ball);
        glMaterialfv(GL_FRONT, GL_SPECULAR,specular_coeffs_ball);
	

	draw_ball();



    glutSwapBuffers();
}

static void draw_ball(){

	glPushMatrix();
	glColor3f(1,1,0);
	glRotatef(posX,1,0,0);
	glRotatef(posZ,0,0,1);
	glTranslatef(posX,0.04,posZ);
	glutSolidSphere(0.05,40,40);
	glPopMatrix();

}


static void draw_wall(float t,float x, float z){

	glPushMatrix();
	glTranslatef(0.5,0.5*t,1);
	glScalef(x,t,z);
	glutSolidCube(1.0);
	glPopMatrix();

}

//Funkcija za crtanje unutrasnjosti lavirinta:
static void draw_labyrinth(){


	GLfloat ambient_coeffs_wall2[]={1,0.1,0,0};
        GLfloat diffuse_coeffs_wall2[]={1,0.3,0,0};
        GLfloat specular_coeffs_wall2[]={0.8,0.7,0.8,0};
        GLfloat shininess_wall2=30;

        glMaterialf(GL_FRONT, GL_SHININESS,shininess_wall2);
        glMaterialfv(GL_FRONT, GL_AMBIENT,ambient_coeffs_wall2);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,diffuse_coeffs_wall2);
        glMaterialfv(GL_FRONT, GL_SPECULAR,specular_coeffs_wall2);
	
	
	glPushMatrix();
	glRotatef(90,0,0,1);
	x=0.5;
	z=1.6;
	glTranslatef(-0.2,-1.8,0.2);
	draw_wall(0.1,x,z);
	glPopMatrix(); 

	//pokretni zidovi:
	

	glPushMatrix();
	glRotatef(90,0,0,1);
	x=0.5;
	t=0.03;
	z=1.4;
	glTranslatef(-0.2,-1.5,wall1Z);
	draw_wall(0.1,x,z);
	glPopMatrix(); 
	


	glPushMatrix();
	glRotatef(90,0,0,1);
	x=0.5;
	t=0.03;
	z=1.4;
	glTranslatef(-0.2,-1.3,-wall1Z);
	draw_wall(0.1,x,z);
	glPopMatrix(); 

	glPushMatrix();
	glRotatef(90,0,0,1);
	x=0.5;
	
	z=1.4;
	glTranslatef(-0.2,-1.0,0.3);
	draw_wall(0.1,x,z);
	glPopMatrix(); 

	glPushMatrix();
	glRotatef(90,0,0,1);
	x=0.5;
	z=0.2;
	glTranslatef(-0.2,-1.0,-0.75);
	draw_wall(0.1,x,z);
	glPopMatrix(); 

	glPushMatrix();
	glRotatef(90,0,0,1);
	x=0.5;
	z=0.5;
	glTranslatef(-0.2,-0.7,-0.75);
	draw_wall(0.1,x,z);
	glPopMatrix(); 

	glPushMatrix();
	glRotatef(90,0,0,1);
	x=0.5;
	t=0.03;
	z=0.7;
	glTranslatef(-0.2,-0.7,0);
	draw_wall(0.1,x,z);
	glPopMatrix(); 


	glPushMatrix();
	glRotatef(90,0,0,1);
	x=0.5;
	t=0.03;
	z=0.2;
	glTranslatef(-0.2,-0.7,wall1Z+0.6);
	draw_wall(0.1,x,z);
	glPopMatrix(); 

	glPushMatrix();
	glRotatef(90,0,0,1);
	x=0.5;
	z=1.5;
	glTranslatef(-0.2,-0.4,0);
	draw_wall(0.1,x,z);
	glPopMatrix(); 


	glPushMatrix();
	glRotatef(90,0,0,1);
	x=0.5;
	z=0.3;
	glTranslatef(-0.2,-0.4,wall1Z+0.5);
	draw_wall(0.1,x,z);
	glPopMatrix(); 


}
