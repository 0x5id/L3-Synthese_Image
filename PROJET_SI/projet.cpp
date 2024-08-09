/********************************************************/
/*                     projet.cpp                                                 */
/********************************************************/
/*                crée a l'ecran une tortue en 3D                      */
/********************************************************/
/*         Les textures ne sont pas présentes car
      je n'ai pas réussis à les integrer correctement.
         Pour rappel l'animation de lance avec "y"                                  */
/********************************************************/
/* inclusion des fichiers d'en-tete freeglut */

#ifdef __APPLE__

#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif
#include <cstdio>
#include <cstdlib>
#include <cmath>
#ifdef __WIN32
#pragma comment (lib, "jpeg.lib")
#endif
#include <jpeglib.h>
#include <unistd.h>



#define PI 3.1415926


/*class Point, sert à creer chaque partie de la tortue*/
class Point{
    public :
	//coordonnées x, y et z du point
	double x;
	double y;
	double z;
	// couleur r, v et b du point
	float r;
	float g;
	float b;
};
//Tableau pour stocker les sommets de la carapace et leur couleur
Point pCarapace[20]={
    {-0.5, 0, 1, 1.0,0.0,0.0},      // point 0
    { 1.8, 0, 1, 0.0,1.0,0.0},     // point 1
    { 1.8, 0, -1, 0.0,0.0,1.0},    // point 2
    { -0.5, 0, -1, 1.0,1.0,1.0},   // point 3

    { -0.3,0.1, 0.85, 1.0,0.0,0.0},      // point 4
    { 1.7, 0.1, 0.85, 0.0,1.0,0.0},      // point 5
    { 1.7, 0.1, -0.85, 0.0,0.0,1.0},     // point 6
    { -0.3, 0.1, -0.85, 1.0,1.0,1.0},    // point 7

    { 0.1,0.4, 0.6, 1.0,0.0,0.0},      // point 8
    { 1.4, 0.4, 0.6, 0.0,1.0,0.0},      // point 9
    { 1.4, 0.4, -0.6, 0.0,0.0,1.0},     // point 10
    { 0.1, 0.4, -0.6, 1.0,1.0,1.0},   // point 11

    { 0.3,0.45, 0.5, 1.0,0.0,0.0},      // point 12
    { 1.2, 0.45, 0.5, 0.0,1.0,0.0},      // point 13
    { 1.2, 0.45, -0.5, 0.0,0.0,1.0},     // point 14
    { 0.3, 0.45, -0.5, 1.0,1.0,1.0},    // point 15

    { 0.7,0.55, 0.1, 1.0,0.0,0.0},      // point 16
    { 1.0, 0.55, 0.1, 0.0,1.0,0.0},      // point 17
    { 1.0, 0.55, -0.1, 0.0,0.0,1.0},     // point 18
    { 0.7, 0.55, -0.1, 1.0,1.0,1.0},    // point 19


    };

//Tableau pour stocker les indices des sommets par face pour la carapace
int fCarapace[18][4]={

  {0,1,5,4},
  {1,2,6,5},
  {2,3,7,6},
  {0,4,7,3},
  {4,5,9,8},
  {5,6,10,9},
  {6,7,11,10},
  {4,8,11,7},

  {8,9,13,12},
  {9,10,14,13},
  {10,11,15,14},
  {8,12,15,11},

  {12,13,17,16},
  {13,14,18,17},
  {14,15,19,18},
  {12,16,19,15},

  {16,17,18,19}};



//Tableau pour stocker les sommets du corps et leur couleur
  Point pcorps[12]={
    {-0.5, 0, 1, 1.0,0.0,0.0},      // point 0
    { 1.8, 0, 1, 0.0,1.0,0.0},     // point 1
    { 1.8, 0, -1, 0.0,0.0,1.0},    // point 2
    { -0.5, 0, -1, 1.0,1.0,1.0},   // point 3

    {-0.3, -0.15, 0.8,0.0,0.0},      // point 4
    { 1.6, -0.15, 0.8, 0.0,1.0,0.0},     // point 5
    { 1.6, -0.15, -0.8, 0.0,0.0,1.0},    // point 6
    { -0.3, -0.15, -0.8, 1.0,1.0,1.0},     // point 7

    {-0.05, -0.3, 0.3,0.0,0.0},      // point 8
    { 1.3, -0.3, 0.3, 0.0,1.0,0.0},     // point 9
    { 1.3, -0.3, -0.3, 0.0,0.0,1.0},    // point 10
    { -0.05, -0.3, -0.3, 1.0,1.0,1.0},     // point 11





    };

//Tableau pour stocker les indices des sommets par face pour le corps
int fcorps[18][4]={
  {0,1,5,4},
  {1,2,6,5},
  {2,3,7,6},
  {0,4,7,3},
  {4,5,9,8},
  {5,6,10,9},
  {6,7,11,10},
  {4,8,11,7},
  {8,9,10,11}
};

//Tableau pour stocker les sommets de la tête et leur couleur
Point pTete[12]={
{-0.4, 1, 0.2, 1.0,0.0,0.0},      // point 0
{ 0.2, 1, 0.2, 0.0,1.0,0.0},     // point 1
{ 0.2, 1, -0.2, 0.0,0.0,1.0},    // point 2
{ -0.4, 1, -0.2, 1.0,1.0,1.0},   // point 3

{ -0.4, 0.7, -0.2, 1.0,1.0,1.0},      // point 4
{ 0, 0.7, -0.2, 0.0,0.0,1.0},     // point 5
{ 0.0, 0.6, -0.2, 0.0,0.0,1.0},    // point 6
{ 0.2, 0.6, -0.2, 0.0,0.0,1.0},     // point 7

{ 0.2, 0.6, 0.2, 0.0,1.0,0.0},      // point 8
{ 0.0, 0.6, 0.2, 0.0,1.0,0.0},     // point 9
{ 0  , 0.7, 0.2, 0.0,0.0,1.0},    // point 10
{-0.4, 0.7, 0.2, 1.0,0.0,0.0}     // point 11
};

//Tableau pour stocker les indices des sommets par face pour le cube
int fTete[6][4]={
  //face envers endroit={0,3,2,1}
  {0,1,2,3},
  {1,2,7,8},
  {8,7,6,9},
  {5,6,9,10},
  {4,5,10,11},
  {0,3,4,11},
  };

  int fTeteCote[2][6]={
  {1,0,11,10,9,8},
  {2,3,4,5,6,7}
  };

//Tableau pour stocker les sommets de la bouche et leur couleur
 Point pBouche[8]={
    {-0.4, 0.7, 0.2, 1.0,0.0,0.0},      // point 0
    { 0  , 0.7, 0.2, 0.0,0.0,1.0},     // point 1
    { 0, 0.7, -0.2, 0.0,0.0,1.0},    // point 2
    { -0.4, 0.7, -0.2, 1.0,1.0,1.0},   // point 3

    { -0.4, 0.6, 0.2, 0.0,1.0,0.0},      // point 4
    { 0.0, 0.6, 0.2, 0.0,1.0,0.0},     // point 5
    { 0.0, 0.6, -0.2, 0.0,0.0,1.0},    // point 6
    { -0.4, 0.6, -0.2, 0.0,0.0,1.0},     // point 7
    };

//Tableau pour stocker les indices des sommets par face pour le cube
int fBouche[6][4]={
  //face envers endroit={0,3,2,1}
  {0,1,2,3},
  {0,1,5,4},
  {0,3,7,4},
  {3,2,6,7},
  {1,2,6,5},
  {4,5,6,7},
  };

//Tableau pour stocker les sommets du pied et leur couleur
Point pPied[8]={
{-0.4, 0.7, 0.2, 1.0,0.0,0.0},      // point 0
{ 0.5  , 0.7, 0.2, 0.0,0.0,1.0},     // point 1
{ 0.5, 0.7, -0.2, 0.0,0.0,1.0},    // point 2
{ -0.4, 0.7, -0.2, 1.0,1.0,1.0},   // point 3

{ -0.4, 0.6, 0.2, 0.0,1.0,0.0},      // point 4
{ 0.8, 0.6, 0.2, 0.0,1.0,0.0},     // point 5
{ 0.8, 0.6, -0.2, 0.0,0.0,1.0},    // point 6
{ -0.4, 0.6, -0.2, 0.0,0.0,1.0},     // point 7
};





//Tableau pour stocker les indices des sommets par face pour le cube
int fPied[6][4]={
  {0,1,2,3},
  {0,1,5,4},
  {0,3,7,4},
  {3,2,6,7},
  {1,2,6,5},
  {4,5,6,7},
  };


char presse;                               // boutton souris
int anglex=-25,angley=40,x,y,xold,yold;

/* Prototype des fonctions */

// initialisation des fonctions
void affichage();
void zoom(int touche);
void clavier(unsigned char touche,int x,int y);
void reshape(int x,int y);
void idle();
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x,int y);
void clavierSpecial(int touche, int x, int y);
void repere();
void carapace();
void corps();
void cylindre(float r, float h, int subdivision);
void cou();
void tete();
void yeux();
void bouche();
void pied();
void allpied(); // tout les pieds
void oeuf();
void animeTouche();
void animeauto();
void lumiere();
void loadJpegImage(char *fichier, int iheight, int iwidth,unsigned char image[] );

// variables qui permettent d'enchainer les allés retour dans l'animation auto
bool boolAnimAuto = true;
bool boolAnimTouche = true;


// variables pour la fonction d'animation à l'aide d'une touche et l'animation automatique
double animationTouche=0;
double animationToucheSpeed= 0.2/12;
double animationAuto = 0;
double animationAutoSpeed= 1.5;
double Max = 30;

// variables pour le zoom/dezoom caméra
float camZoom = 1.3;
float zoomSpeed = 0.1;
float moveSpeed = 1.3;

//variables pour les lumières
GLfloat source[]= {0.0, 2.0, 1.0,1.0} ;
GLfloat dir[]= {0.0, 0.0,0.5,0.0} ;
GLfloat dif[]= {2.0, 4.0,0.5,1.0} ;
GLfloat amb[]= {1.5, 1.0,0.5,1.0} ;
GLfloat spec[]= {1.0, 1.0,1.0,1.0} ;
GLfloat shininess[]={50.0};


// variables pour la texture
/*
const unsigned int iwidth = 256;
const unsigned int iheight = 256;
unsigned char image[iwidth*iheight*3];
unsigned char texture[iheight][iwidth][4];

const unsigned int iwidth2 = 256;
const unsigned int iheight2 = 256;
unsigned char image2[iwidth2*iheight2*3];
unsigned char texture2[iheight2][iwidth2][4];
*/




int main(int argc,char **argv)
{
  /* initialisation de glut et creation
     de la fenetre */
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(200,200);
  glutInitWindowSize(1000,700);
  glutCreateWindow("tortue de mer");

  /* Initialisation d'OpenGL */

  //glClearColor(0.0,0.0,0.0,0.0); //fond noir
  glClearColor(64.0/255.0,230.0/255.0,212.0/255.0,0.0);
  glColor3f(1.0,1.0,1.0);
  glPointSize(2.0);
  glEnable(GL_DEPTH_TEST);


  /* enregistrement des fonctions de rappel */
  glutDisplayFunc(affichage);
  glutKeyboardFunc(clavier);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(mousemotion);
  glutSpecialFunc(clavierSpecial);
  glutIdleFunc(animeauto);


  /* Entree dans la boucle principale glut */
  glutMainLoop();
  return 0;
}


void affichage()
{

  /* effacement de l'image avec la couleur de fond */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glShadeModel(GL_SMOOTH);

  glLoadIdentity();
  glOrtho(camZoom,-camZoom,-0.4 * camZoom, 1.6 * camZoom ,-camZoom,camZoom); // camZoom est modifié par la fonction zoom qui permet de zoomer et dezoomer
  glRotatef(angley,1.0,0.0,0.0);
  glRotatef(anglex,0.0,1.0,0.0);


   // Dessin du cube

// repere();
carapace();
corps();
cou();
tete();
allpied();
lumiere();
// oeuf();   //fait apparaitre un cylindre mais n'ayant pas réussi à appliquer la texture il est inutile

/*
loadJpegImage("./tortue.jpg",iheight,iwidth,image);
texture();
*/

glFlush();
  //On echange les buffers
glutSwapBuffers();
}



void repere(){
     //Repère X,Y,Z
    //axe x en rouge
    glBegin(GL_LINES);
        glColor3f(1.0,0.0,0.0);
    	glVertex3f(0, 0,0.0);
    	glVertex3f(1, 0,0.0);
    glEnd();
    //axe des y en vert
    glBegin(GL_LINES);
    	glColor3f(0.0,1.0,0.0);
    	glVertex3f(0, 0,0.0);
    	glVertex3f(0, 1,0.0);
    glEnd();
    //axe des z en bleu
    glBegin(GL_LINES);
    	glColor3f(0.0,0.0,1.0);
    	glVertex3f(0, 0,0.0);
    	glVertex3f(0, 0,1.0);
    glEnd();
}



//fonction qui permet de creer la "carapace" de la tortue, la partie supérieure soit la partie verte
// à l'aide des points pCarapace et des faces fCarapace

void carapace(){
int i,j;

 glPushMatrix();
 glTranslatef(-0.35, 0.3, 0);

for (i=0;i<18;i++)
    {
      glBegin(GL_LINE_LOOP); //boucle qui affiche les arêtes
      for (j=0;j<4;j++){
          glColor3f(0,0,0);
          glVertex3f(pCarapace[fCarapace[i][j]].x*0.5,pCarapace[fCarapace[i][j]].y*0.5,pCarapace[fCarapace[i][j]].z*0.5);
      }
      glEnd();
    }

  for (i=0;i<18;i++)
    {
      glBegin(GL_POLYGON); //boucle qui crée les faces
      for (j=0;j<4;j++){
          glColor3f(0,230,0);
          glVertex3f(pCarapace[fCarapace[i][j]].x*0.5,pCarapace[fCarapace[i][j]].y*0.5,pCarapace[fCarapace[i][j]].z*0.5);
      }
      glEnd();
    }

 glPopMatrix();
    };




// fonction qui permet de creer la partie bas du corps à l'aide des points pcorps et des faces fcorps

void corps(){
int i,j;
   glPushMatrix();
   glTranslatef(-0.35, 0.3, 0);


for (i=0;i<18;i++)
    {
      glBegin(GL_LINE_LOOP);   //boucle qui affiche les arêtes
      for (j=0;j<4;j++){
          glColor3f(0,0,0);
          glVertex3f(pcorps[fcorps[i][j]].x*0.5,pcorps[fcorps[i][j]].y*0.5,pcorps[fcorps[i][j]].z*0.5);
      }
      glEnd();
    }

  for (i=0;i<18;i++)
    {
      glBegin(GL_POLYGON); //boucle qui crée les faces
      for (j=0;j<4;j++){
          glColor3f(0.4,0.2,0.05);
          glVertex3f(pcorps[fcorps[i][j]].x*0.5,pcorps[fcorps[i][j]].y*0.5,pcorps[fcorps[i][j]].z*0.5);
      }
      glEnd();
    }

 glPopMatrix();
}


// primitive cylindre
//fonction cylindre qui va permettre de créer le cou à l'aide de deux cylindres ainsi que les yeux avec un seul cylindre
// un oeuf à aussi été fait avec mais  annulé car je n'arrive pas à mettre les textures
void cylindre(float r, float hauteur, int subdivision)
{
    float coo[subdivision * 2][3];

    for(int i = 0; i < subdivision * 2; i++) // principe de subdivision
    {
        float angle = 2*PI/float(subdivision)*i;
        coo[i][0] = r * cos(angle);
        coo[i][1] = r * sin(angle);

        if(i >= subdivision)
        {
            coo[i][2] = hauteur / 2.0;
        }
        else
        {
            coo[i][2] = -hauteur / 2.0;
        }

    }
    int faces[subdivision][4];

    // 4 faces initiales pour la création du cylindre, plus il a y a de subdivision plus il y a de faces
    for(int i = 0; i < subdivision; i++)
    {
        faces[i][0] = i;
        faces[i][1] = (i+1)%subdivision;
        faces[i][2] = (i + 1)%subdivision + subdivision;
        faces[i][3] = i + subdivision;
    }

    for(int i = 0; i < subdivision; i++) // boucle permettant d'afficher les faces avec leurs subdivisions
    {
        glBegin(GL_QUADS);
            glVertex3f(coo[faces[i][0]][0], coo[faces[i][0]][1], coo[faces[i][0]][2]);
            glVertex3f(coo[faces[i][1]][0], coo[faces[i][1]][1], coo[faces[i][1]][2]);
            glVertex3f(coo[faces[i][2]][0], coo[faces[i][2]][1], coo[faces[i][2]][2]);
            glVertex3f(coo[faces[i][3]][0], coo[faces[i][3]][1], coo[faces[i][3]][2]);
        glEnd();
    }

// faces au extrémités du cylindre
    for(int i = 0; i < subdivision; i++)
    {
        glBegin(GL_POLYGON);

            glVertex3f(coo[i][0], coo[i][1], coo[i][2]);
            glVertex3f(0, 0, -hauteur / 2.0);
            glVertex3f(coo[(i + 1) % subdivision][0], coo[(i + 1) % subdivision][1], coo[(i + 1) % subdivision][2]);
        glEnd();
    }

    for(int i = 0; i < subdivision; i++)
    {
        glBegin(GL_POLYGON);
            glNormal3f(0, 0, 1);
            glVertex3f(coo[(i + 1) % subdivision + subdivision][0], coo[(i + 1) % subdivision + subdivision][1], coo[(i + 1) % subdivision + subdivision][2]);
            glVertex3f(0, 0, hauteur / 2.0);
            glVertex3f(coo[i + subdivision][0], coo[i + subdivision][1], coo[i + subdivision][2]);
        glEnd();
    }
}




// fontion qui fait appel à cylyndre.cpp pour créer les cou qui est composé de deux cylindres

void cou(){
glPushMatrix();

glTranslatef(0.55+animationTouche,0.3, 0);
glRotatef(90, 0, 1, 0);
glColor3f(0.9,0.8,0.6);
  cylindre (0.05,0.2,20); //cou 1

glPopMatrix();

glPushMatrix();

glTranslatef(0.55+animationTouche,0.3, 0);
glRotatef(90, -25, 90, 0);
glColor3f(0.9,0.8,0.6);
  cylindre (0.05,0.3,20); // cou2

glPopMatrix();
}







// fonction qui crée la partie verte de la tête, mais qui appel aussi la fonction bouche et yeux pour afficher entièremment la tête
// à l'aide des points pTete et des faces fTete ainsi que fTeteCote (fTeteCote est à part car le coté est à 6 points donc 6 arêtes par coté

void tete(){
int i,j;
glPushMatrix();

    glTranslatef(0.72+animationTouche,-0.07, 0);
    glRotatef(180, 0, 1, 0);
    glColor3f(0.7,1.0,0.0);

for (i=0;i<6;i++)
    {
      glBegin(GL_LINE_LOOP);   //boucle qui affiche les arêtes
      for (j=0;j<4;j++){
          glColor3f(0,0,0);
          glVertex3f(pTete[fTete[i][j]].x*0.5,pTete[fTete[i][j]].y*0.5,pTete[fTete[i][j]].z*0.5);
      }
      glEnd();
    }

  for (i=0;i<6;i++)
    {
      glBegin(GL_POLYGON);   //boucle qui crée les faces
      for (j=0;j<4;j++){
          glColor3f(0,230,0);
          glVertex3f(pTete[fTete[i][j]].x*0.5,pTete[fTete[i][j]].y*0.5,pTete[fTete[i][j]].z*0.5);
      }
      glEnd();
    }

    for (i=0;i<2;i++)
    {
      glBegin(GL_LINE_LOOP);  //boucle qui affiche les arêtes sur les cotés de la tête
      for (j=0;j<6;j++){
          glColor3f(0,0,0);
          glVertex3f(pTete[fTeteCote[i][j]].x*0.5,pTete[fTeteCote[i][j]].y*0.5,pTete[fTeteCote[i][j]].z*0.5);
      }
      glEnd();
    }

    for (i=0;i<2;i++)
    {
      glBegin(GL_POLYGON);    //boucle qui crée les faces sur les cotés de la tête
      for (j=0;j<6;j++){
          glColor3f(0,230,0);
          glVertex3f(pTete[fTeteCote[i][j]].x*0.5,pTete[fTeteCote[i][j]].y*0.5,pTete[fTeteCote[i][j]].z*0.5);
      }
      glEnd();
    }

bouche(); // affiche la bouche (plus simple pour le déplacement dans l'animation)
yeux(); // affiche les yeux

glPopMatrix();

};

// fonction qui permet de créer les yeux à l'aide d'un cylindre qui traverse la tête pour laisser apparaitre les bouts des deux cotés
void yeux(){

glPushMatrix();
glColor3f(0,0,0);
glTranslatef(-0.1,0.45, 0);
cylindre (0.04,0.24,5);  //yeux
glPopMatrix();


}

// fonction qui permet de créer la bouche à l'aide des points pBouche et des faces fBouche
void bouche(){
int i,j;

for (i=0;i<6;i++)
    {
      glBegin(GL_LINE_LOOP);   //boucle qui affiche les arêtes
      for (j=0;j<4;j++){
          glColor3f(0,0,0);
          glVertex3f(pBouche[fBouche[i][j]].x*0.5,pBouche[fBouche[i][j]].y*0.5,pBouche[fBouche[i][j]].z*0.5);
      }
      glEnd();
    }

  for (i=0;i<6;i++)
    {
      glBegin(GL_POLYGON);    //boucle qui crée les faces
      for (j=0;j<4;j++){
          glColor3f(0.9,0.8,0.6);
          glVertex3f(pBouche[fBouche[i][j]].x*0.5,pBouche[fBouche[i][j]].y*0.5,pBouche[fBouche[i][j]].z*0.5);
      }
      glEnd();
    }

}



// fonction qui permet de créer un seul pied à l'aide des points pPied et des faces fPied
void pied(){

int i,j;

for (i=0;i<6;i++)
    {
      glBegin(GL_LINE_LOOP);  //boucle qui affiche les arêtes
      for (j=0;j<4;j++){
          glColor3f(0,0,0);
          glVertex3f(pPied[fPied[i][j]].x*0.5,pPied[fPied[i][j]].y*0.5,pPied[fPied[i][j]].z*0.5);
      }
      glEnd();
    }

  for (i=0;i<6;i++)
    {

      glBegin(GL_POLYGON);   //boucle qui crée les faces

      for (j=0;j<4;j++){

          glColor3f(0.9,0.8,0.6);
          glVertex3f(pPied[fPied[i][j]].x*0.5,pPied[fPied[i][j]].y*0.5,pPied[fPied[i][j]].z*0.5);
      }
      glEnd();
    }

}






//fonction qui permet de créer les 4 pieds en appellant la fonction pied() 4 fois
void allpied(){
glPushMatrix(); // pied arrière droit
glTranslatef(-0.5,-0.07, 0.23);
       glRotatef(180, 0, 1, 0);

pied();
glPopMatrix();


glPushMatrix(); // pied arrière gauche
glTranslatef(-0.5,-0.07, -0.23);
       glRotatef(180, 0, 1, 0);

pied();
glPopMatrix();

glPushMatrix(); // pied avant gauche
glTranslatef(0.22,-0.07, 0.42);
       glRotatef(-120+animationAuto, 0, 1, 0); // ici on ajoute la var animationAuto pour que le pied s'anime

pied();
glPopMatrix();

glPushMatrix();  // pied avant droit
glTranslatef(0.22,-0.07, -0.42);
       glRotatef(120+animationAuto, 0, 1, 0); // ici on ajoute la var animationAuto pour que le pied s'anime

pied();
glPopMatrix();


};




//fait apparaitre un cylindre mais n'ayant pas réussi à appliquer la texture la fonction est inutile

void oeuf(){

glPushMatrix();
glTranslatef(0.22,0.3, 1);
cylindre (0.1,0.1,5); //oeuf

glPopMatrix();
}


// fonction qui permet de lancer l'animation par touche à l'aide de la touche "y"
void animeTouche(){

if (boolAnimTouche && animationTouche<0){ // si le bool est true et que la tête est dans la carapace l'animation auto fera sortir la tête

animationTouche += animationToucheSpeed;
glutPostRedisplay();

}

else if (!boolAnimTouche && animationTouche>=-0.6) // si le bool est false et que la tête est en dehors de la carapace l'animation auto fera rentrer la tête
{
animationTouche -= animationToucheSpeed;

}

glutPostRedisplay();
}





//fonction qui permet d'avoir une animation automatique et permanente
void animeauto()
{
if (boolAnimAuto)
{
        animationAuto+= animationAutoSpeed;  // allé de l'animation auto
        if(animationAuto>=Max)
        {
            boolAnimAuto= false;

        }
    }
    else if(!boolAnimAuto)
    {
        animationAuto-= animationAutoSpeed; // retour de l'animation
        if(animationAuto<=-Max)
        {
            boolAnimAuto = true;
        }
    }

    glutPostRedisplay();

animeTouche();
}


// fonction qui permet de zoomer à l'aide de "Z" et dézoomer avec "z"
  void zoom(int touche)
{
	camZoom += touche * zoomSpeed;
}


// fonction qui génère la lumière
void lumiere(){
glEnable(GL_LIGHTING);
glEnable(GL_COLOR_MATERIAL);

glLightfv(GL_LIGHT0, GL_POSITION, source);
glLightfv(GL_LIGHT0, GL_AMBIENT,amb);
glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
glLightfv(GL_LIGHT0, GL_SPECULAR, spec );
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);

glEnable(GL_COLOR_MATERIAL);
glEnable(GL_LIGHT0);
};



/* void loadJpegImage(char *fichier, int iheight, int iwidth,unsigned char image[] )
{
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *file;
    unsigned char *ligne;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
#ifdef __WIN32
    if (fopen_s(&file,fichier,"rb") != 0)
    {
        fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
        exit(1);
    }
#elif __GNUC__
    if ((file = fopen(fichier,"rb")) == 0)
    {
        fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
        exit(1);
        unsigned char texture[iheight][iwidth][3];
    }
#endif
    jpeg_stdio_src(&cinfo, file);
    jpeg_read_header(&cinfo, TRUE);

    if ((cinfo.image_width!=iwidth)||(cinfo.image_height!=iheight))
    {
        fprintf(stdout,"Erreur : l'image n'est pas de taille %dx%d\n",iheight,iwidth);
        exit(1);
    }
    if (cinfo.jpeg_color_space==JCS_GRAYSCALE)
    {
        fprintf(stdout,"Erreur : l'image doit etre de type RGB\n");
        exit(1);
    }

    jpeg_start_decompress(&cinfo);
    ligne=image;
    while (cinfo.output_scanline<cinfo.output_height)
    {
        ligne=image+3*iwidth*cinfo.output_scanline;
        jpeg_read_scanlines(&cinfo,&ligne,1);
    }
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);


}
void textures()
{
    for(int i =0; i<iheight; i++)
    {
        for(int j =0; j<iwidth; j++)
        {
            texture[i][j][0]= image[i*iwidth*3+j*3];
            texture[i][j][1]= image[i*iwidth*3+j*3+1];
            texture[i][j][2]= image[i*iwidth*3+j*3+2];
            texture[i][j][3]= 255;

        }
    }

    for(int i =0; i<iheight2; i++)
    {
        for(int j =0; j<iwidth2; j++)
        {
            texture2[i][j][0]= image2[i*iwidth2*3+j*3];
            texture2[i][j][1]= image2[i*iwidth2*3+j*3+1];
            texture2[i][j][2]= image2[i*iwidth2*3+j*3+2];
            texture2[i][j][3]= 255;

        }
    }

}
*/



// touches clavier

void clavier(unsigned char touche,int x,int y)
{
  switch (touche)
    {
    case 'p': /* affichage du carre plein */
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glutPostRedisplay();
      break;
    case 'f': /* affichage en mode fil de fer */
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      glutPostRedisplay();
      break;
    case 's' : /* Affichage en mode sommets seuls */
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      glutPostRedisplay();
      break;
    case 'd':
      glEnable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'D': // "x-ray"
      glDisable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'a':
      glPolygonMode(GL_FRONT,GL_FILL);
      glPolygonMode(GL_FRONT,GL_LINE);
      glutPostRedisplay();
    break;
    case 'z': // dézoom
      zoom(1);
      glutPostRedisplay();
    break;
    case 'Z': // zoom
      zoom(-1);
      glutPostRedisplay();
    break;
    case 'y': // lance l'animation
      boolAnimTouche = !boolAnimTouche;
    break;

    case 'q' : /*la touche 'q' permet de quitter le programme */
      exit(0);


    }
}

// touches clavier flèches permetant de bouger la caméra
void clavierSpecial(int fleche, int x, int y)
{
	switch (fleche)
	{
    case GLUT_KEY_LEFT: //Deplacer la cam a droite
     anglex=anglex+moveSpeed;
         break;
    case GLUT_KEY_RIGHT: //Deplacer la cam a gauche
     anglex=anglex-moveSpeed;
    break;
    case GLUT_KEY_UP: //Deplacer la cam par le bas
     angley=angley-moveSpeed;
    break;
    case GLUT_KEY_DOWN: //Deplacer la cam par le haut
     angley=angley+moveSpeed;
    break;
	}
glutPostRedisplay();
}



//reshape
void reshape(int x,int y)
{
  if (x<y)
    glViewport(0,(y-x)/2,x,x);
  else
    glViewport((x-y)/2,0,y,y);


}




// déplace caméra souris
void mouse(int button, int state,int x,int y)
{
  /* si on appuie sur le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    presse = 1; /* le booleen presse passe a 1 (vrai) */
    xold = x; /* on sauvegarde la position de la souris */
    yold=y;
  }
  /* si on relache le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    presse=0; /* le booleen presse passe a 0 (faux) */
}







void mousemotion(int x,int y)
  {
    if (presse) /* si le bouton gauche est presse */
    {
      /* on modifie les angles de rotation de l'objet
	 en fonction de la position actuelle de la souris et de la derniere
	 position sauvegardee */
      anglex=anglex+(x-xold);
      angley=angley+(y-yold);
      glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
    }

    xold=x; /* sauvegarde des valeurs courante de le position de la souris */
    yold=y;
  }
