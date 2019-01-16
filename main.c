#include<stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include<math.h>
#define TIMER_INTERVAL 40
#define TIMER_ID 0
#include "image.h"
#define FILENAME0 "wall.bmp"
static GLuint names[1];
static int window_width, window_height;
static float matrix[16]; //matrica za teksture



float wall1Z=0.3;
float wall2Z;
float wall3Z;
int wall_direction=-1;
float x=0;
float t=0;
float z=0;
float xpos=0, ypos=0,  zpos=0, cRadius=1,xrot=0, yrot=0,angle=0;
const static float pi = 3.141592653589793;
float lastx, lasty;
float kx=0,ky=0.1,kz=1,lx=0,lz=0,r=1;
static void draw_wall(float t,float x,float z);
static void draw_labyrinth();
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void draw_ball();
static void on_timer(int value);

static int  check_function(); //proverava da li se kuglica sudara sa zidom
static void right_func();//na osnovu ugla rotacije preko tastature, odredjuje se kretanje loptice udesno
static void left_func();//na osnovu ugla rotacije preko tastature, odredjuje se kretanje loptice ulevo
static void up_func();//na osnovu ugla rotacije preko tastature, odredjuje se kretanje loptice nagore
static void down_func();//na osnovu ugla rotacije preko tastature, odredjuje se kretanje loptice nadole
static void increment_x();//povecava se x koordinata loptice
static void increment_z();//povecava se z koordinata loptice
static void dec_x();//smanjuje se x koordinata loptice
static void dec_z();//smanjuje se z koordinata loptice 

 void processSpecialKeys(int key, int xx, int yy) {
        
	switch (key) {
		case GLUT_KEY_LEFT :
                    //pomeramo poziciju kamere pomocu leve strelice na tastaturi
			angle -= 0.05f;
			if(angle<=-360)
                         angle+=360;
                        lx = sin(angle);
                        lz =-cos(angle);
                        
                        break;
                case GLUT_KEY_RIGHT :
                     //pomeramo poziciju kamere pomocu desne strelice na tastaruri
                         angle += 0.05f;
                         if(angle>=360)
                           angle-=360;
                          lx = sin(angle);
                          lz =-cos(angle);
                        
                        break;
                case GLUT_KEY_UP :
                        r -= 0.5;
                       
                          
                            break;
                case GLUT_KEY_DOWN :
                        
                       //zumiramo
                       if(r+0.5>60)
                             r=60;
                         r += 0.5;
                            
                        break;
            }
        
            
	glutPostRedisplay();
}
void camera (void) {
    glRotatef(xrot,1.0,0.0,0.0);  
    glRotatef(yrot,0.0,1.0,0.0);  
    glTranslated(-xpos,-ypos,-zpos);
    glutPostRedisplay();
}
static void initialize(void)
{
    // Objekat koji predstavlja teskturu ucitanu iz fajla. 
    Image * image;

    // Ukljucuje se testiranje z-koordinate piksela. 
    glEnable(GL_DEPTH_TEST);

    /* Ukljucuju se teksture. */
    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

    //Inicijalizuje se objekat koji ce sadrzati teksture ucitane iz fajla.
     
    image = image_init(0, 0);

    /* Kreira se prva tekstura. */
    image_read(image, FILENAME0);

    // Generisu se identifikatori tekstura. 
    glGenTextures(1, names);

    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    glBindTexture(GL_TEXTURE_2D, 0);

    // Unistava se objekat za citanje tekstura iz fajla. 
    image_done(image);

    // Inicijalizujemo matricu rotacije. 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
}


int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);


    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lavirint");

    
    glutSpecialFunc(processSpecialKeys);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    glClearColor(0.68,0.98,0.68,0);
     initialize();
    
    glLineWidth(2);
    glutMainLoop();

    return 0;
}


//Funkcija koja proverava da li ce kuglica udariti u zid
static int check_function(){


	if((kx>=-0.08 && kx<=-0.02) && (kz<=1.04 && kz>=0.56))
		return 1;
//prvi deo
	if((kx>=-0.02 && kx<=0.25) && (kz>=0.16 && kz<=1.93))
		return 1;
//pokretni deo prvog dela
	if((kx>=0.21 && kx<=0.42) && (kz>=1.79 && kz<=1.93)){
		if(wall3Z+1.5<=kz){
		return 1;
		}	
	}
//ulaz za drugi deo
	if((kx>=0.25 && kx<=0.45) && (kz>=0.14 && kz<=0.20))
		return 1;
//drugi deo
	if((kx>=0.42 && kx<=0.56) && (kz>=0.16 && kz<=1.93))
		return 1;
//pokretni deo drugog dela
	if((kx>=0.65 && kx<=0.71) && (kz>=1.41 && kz<=1.93)){
		if(wall2Z+1.4<=kz){
			return 1;
			 }
	}
//ulaz za treci deo
	if((kx>=0.56 && kx<=0.72) && (kz>=0.55 && kz<=0.60))
		return 1;
//treci deo I

//treci deo II

	if((kx>=0.70 && kx<=0.84) && (kz>=0.16 && kz<=1.93))
		return 1;
//ulaz za 4.deo
	if((kx>=0.82 && kx<=1.04) && (kz>=0.40 && kz<=0.56))
		return 1;
//cetvrti deo I:

	if((kx>=1.04 && kx<=1.15) && (kz>=0.16 && kz<=1.93)){
		return 1;
	}
//cetvrti deo II 

	if((kx>=1.14 && kx<=1.36) && (kz>=1.44 && kz<1.93)){
		return 1;
		}


//peti deo(koji je ujedno i zamka da ako pogresno loptica skrene vraca se na pocetak)
	if((kx>=1.25 && kx<=1.52) &&(kz>=0.16 && kz<=1.93)){
		return 1;
		}
//peti deo II
	if((kx>=1.25 && kx<=1.52) && (kz>0.37 && kz<0.55)){
	return 1;
	}


	if((kx>=1.25 && kx<=1.64) && (kz>0.16 && kz<0.55)){
		return 1;
		}


//sesti deo
	if((kx>=1.52 && kx<=1.60) && (kz>0.16 && kz<1.93)){
		return 1;
	}
//ulaz sa sedmi deo
	if((kx>=1.64 && kx<=1.78) && (kz>0.16 && kz<0.37)){	
		return 1;
	}
//sedmi deo i kraj-izlaz iz lavirinta
	if((kx>=1.78 && kx <=1.94) && (kz>0.16 && kz<1.93)){
		return 1;
		}
//kraj
	if((kx>=1.94 && kx<=2.06) && (kz>0.52 && kz<1.05))
		return 1;




	return 0;
}

static void on_timer(int value){
	
	if(value!=TIMER_ID)
	return;
	//namestamo pravac i brzinu za pokretne zidove u lavirintu.
	if(wall_direction==1){
	wall1Z+=0.0001/20;
	}
	else
	wall1Z-=0.0001/20;

	if(wall1Z<-0.3 || wall1Z>0.3){
	wall_direction=-wall_direction;
}


	glutPostRedisplay();
	glutTimerFunc(TIMER_INTERVAL,on_timer,TIMER_ID);
}


static void on_keyboard(unsigned char key, int x, int y){
//Podesavamo da se kuglica krece

   switch(key){

	case 27:
	exit(0);
	break;
   //Kuglica se krece napred kada pritisnemo 'w'
	case 'w':
	case 'W':
          up_func();
            break;
   //Kuglica se krece nazad kada pristisnemo 's'
	case 's':
	case 'S':
    	  down_func();
	   break;
        
    
    //Kuglica se krece ulevo kada pritisnemo 'a'
	case 'a':
	case 'A':
          left_func();
	   break;
        
        case 'd':
	case 'D':
           right_func();
	    break;
      
        
    }
    
    
	glutPostRedisplay();
}
static void on_reshape(int width, int height)
{

    window_width = width;
    window_height = height;

	if(height == 0)
		height = 1;
	float ratio = 1.0* width / height;
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glViewport(0, 0, width, height);
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

static void on_display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMultMatrixf(matrix);


    
    glLoadIdentity(); 
//Postavljamo kameru da prati kuglicu.
    gluLookAt(-1+r*lx,2,1+r*lz,
                  kx,ky,kz,
                  0,1,0
    );
    


   /* glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslatef(1,1,1);
    glScalef(2,2,2);
    glutWireCube(1);
    glPopMatrix(); */

    
   /* glPopMatrix();
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
    glEnd();*/


	glutTimerFunc(TIMER_INTERVAL,on_timer,TIMER_ID);
	//Crtamo zidove lavirinta i namestamo boju
	GLfloat light_position[]={2,0,-1,1}; 
	GLfloat ambient_coeffs_l[]={0.0,0.3,1,0};
        GLfloat diffuse_coeffs_l[]={0.3,0.3,1,0};
        GLfloat specular_coeffs_l[]={0.8,0.8,0.3,0};
        GLfloat shininess_l=30;

	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
        glPushMatrix();
        glTranslatef(1,0,1.05);
        glDisable(GL_CULL_FACE);
        glEnable(GL_TEXTURE_2D);
        
        glBindTexture(GL_TEXTURE_2D, names[0]);
        glColor3f(0.5, 0.5, 0.5);   
        glBegin(GL_QUADS);                    ///pravimo postolje

        glTexCoord2f(0, 0);
        glVertex3f(-1.1,0,1.1);

        glTexCoord2f(1, 0);
        glVertex3f(-1.1,0,-1.1);

        glTexCoord2f(1, 0.5);
        glVertex3f(1.1,0,-1.1);

        glTexCoord2f(0, 0.5);
        glVertex3f(1.1,0,1.1);

        
        //Crtamo gornji
        glTexCoord2f(0, 0);
        glVertex3f(-1.1,0,-1.1);
        glTexCoord2f(1, 0);
        glVertex3f(-1.1,-0.3,-1.1);
        glTexCoord2f(1, 0.5);
        glVertex3f(1.1,-0.3,-1.1);
        glTexCoord2f(0, 0.5);
        glVertex3f(1.1,0,-1.1);
        
         //Crtamo desni
        glTexCoord2f(0, 0);
        glVertex3f(1.1,0,1.1);
        glTexCoord2f(1, 0);
        glVertex3f(1.1,-0.3,1.1);
        glTexCoord2f(1, 0.5);
        glVertex3f(1.1,-0.3,-1.1);
        glTexCoord2f(0, 0.5);
        glVertex3f(1.1,0,-1.1);
        //Crtamo levi
         glTexCoord2f(0, 0);
        glVertex3f(-1.1,0,1.1);
        glTexCoord2f(1, 0);
        glVertex3f(-1.1,-0.3,1.1);
        glTexCoord2f(1, 0.5);
        glVertex3f(-1.1,-0.3,-1.1);
        glTexCoord2f(0, 0.5);
        glVertex3f(-1.1,0,-1.1);
        
        //Crtamo donji
        glTexCoord2f(0, 0);
        glVertex3f(1.1,0,1.1);
        glTexCoord2f(1, 0);
        glVertex3f(1.1,-0.3,1.1);
        glTexCoord2f(1, 0.5);
        glVertex3f(-1.1,-0.3,1.1);
        glTexCoord2f(0, 0.5);
        glVertex3f(-1.1,0,1.1);
        
        //Crtamo ispod
         glTexCoord2f(0, 0);
        glVertex3f(-1.1,-0.3,1.1);
        glTexCoord2f(1, 0);
        glVertex3f(-1.1,-0.3,-1.1);
        glTexCoord2f(1, 0.5);
        glVertex3f(1.1,-0.3,-1.1);
        glTexCoord2f(0, 0.5);
        glVertex3f(1.1,-0.3,1.1);
        glEnd();
       
        glBindTexture(GL_TEXTURE_2D, 0);
        glPopMatrix();
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
   
	//Crtanje unutrasnjosti lavirinta
	draw_labyrinth();
    
        glBindTexture(GL_TEXTURE_2D, 0);
	glLightfv(GL_LIGHT0, GL_POSITION,light_position);
        glMaterialf(GL_FRONT, GL_SHININESS,shininess_l);
        glMaterialfv(GL_FRONT, GL_AMBIENT,ambient_coeffs_l);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,diffuse_coeffs_l);
        glMaterialfv(GL_FRONT, GL_SPECULAR,specular_coeffs_l);



	//Crtanje zidova koji cine okvir lavirinta
	
	//Ulaz i zidovi pored
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


	//Izlaz i zidovi pored
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

	//Zidovi sa strane:

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
	


	//Osvetljenje


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

//postavljamo boju za lopticu i crtamo lopticu

	GLfloat ambient_coeffs_ball[]={1,0.1,0,0};
        GLfloat diffuse_coeffs_ball[]={1,0.3,0,0};
        GLfloat specular_coeffs_ball[]={0.6,0.7,0.8,0};
        GLfloat shininess_ball=30;

        glMaterialf(GL_FRONT, GL_SHININESS,shininess_ball);
        glMaterialfv(GL_FRONT, GL_AMBIENT,ambient_coeffs_ball);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,diffuse_coeffs_ball);
        glMaterialfv(GL_FRONT, GL_SPECULAR,specular_coeffs_ball);
	
//Crtamo lopticu
       
        draw_ball();
   


    glutSwapBuffers();
}

static void draw_ball(){

	glPushMatrix();
	glColor3f(1,1,0);
        glTranslatef(kx,ky,kz);
	glutSolidSphere(0.05,40,40);
	glPopMatrix();

}

//Funkcija za crtanje zidova lavirinta 
//Kod za funkciju napisan uz pomoc: https://stackoverflow.com/questions/28547173/creating-a-3d-room-in-opengl-c

static void draw_wall(float t,float x, float z){

	glPushMatrix();
        glNormal3f(0,0,1);
	glTranslatef(0.5,0.5*t,1);
        glScalef(x,t,z);

         glutSolidCube(1);


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


	

	glPushMatrix();
	glRotatef(90,0,0,1);
	x=0.5;
	t=0.03;
	z=1.4;
	glTranslatef(-0.2,-1.5,0.3);
	draw_wall(0.1,x,z);
	glPopMatrix(); 
	


	glPushMatrix();
	glRotatef(90,0,0,1);
	x=0.5;
	t=0.03;
	z=1.4;
	glTranslatef(-0.2,-1.3,-0.3);
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
	wall2Z=wall1Z+0.6;
	glTranslatef(-0.2,-0.7,wall2Z);
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
	wall3Z=wall1Z+0.5;
	glTranslatef(-0.2,-0.4,wall3Z);
	draw_wall(0.1,x,z);
	glPopMatrix(); 


}

//Uvecavamo i smanjujemo koordinate loptice

void increment_z(){

	if(check_function()==0){
	      kx=0;
	      kz=1;
	}
	else 
     	      kz+=0.03;
   
	}
void dec_z(){

	if(check_function()==0){
           kx=0;
           kz=1;
	}
	else 
          kz-=0.03;
   
}
void increment_x(){

	if(check_function()==0){
	      kx=0;
	      kz=1;
	}
	else 
      	      kx+=0.03;
     
}
void dec_x(){
	if(check_function()==0){
     		 kx=0;
    		 kz=1;
	}
	else 
   		 kx-=0.03;
  
	}

void right_func(){
    if((angle>=0 && angle<90) || (angle<0 && angle>=-90)){
        increment_z();
    }
    else if((angle>=90 && angle<180) || (angle<-270 && angle>=-360)){
        dec_x();
    }
    else if((angle>=180 && angle<270) || (angle<-180 && angle>=-270)){
        dec_z();
    }
    else if((angle>=270 && angle<360) ||(angle<-90 && angle>=-180)){
        increment_x();
    }
}
void left_func(){
    if((angle>=0 && angle<90) || (angle<0 && angle>=-90))
        dec_z();
    else if((angle>=90 && angle<180) || (angle<-270 && angle>=-360))
        increment_x();
    else if((angle>=180 && angle<270) || (angle<-180 && angle>=-270))
        increment_z();
    else if((angle>=270 && angle<360) ||(angle<-90 && angle>=-180))
        dec_x();
}
void up_func(){
    
    if((angle>=0 && angle<90) || (angle<0 && angle>=-90))
        increment_x();
    else if((angle>=90 && angle<180) || (angle<-270 && angle>=-360))
        increment_z();
    else if((angle>=180 && angle<270) || (angle<-180 && angle>=-270))
        dec_x();
    else if((angle>=270 && angle<360) ||(angle<-90 && angle>=-180))
        dec_z();
    
}
void down_func(){
    
    if((angle>=0 && angle<90) || (angle<0 && angle>=-90))
        dec_x();
    else if((angle>=90 && angle<180) || (angle<-270 && angle>=-360))
        dec_z();
    else if((angle>=180 && angle<270) || (angle<-180 && angle>=-270))
        increment_x();
    else if((angle>=270 && angle<360) ||(angle<-90 && angle>=-180))
        dec_z();
    
}
