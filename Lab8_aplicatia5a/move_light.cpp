/*
 *  Programul demonstreaza modul de modificare al pozitiei sursei de lumina
 *  utilizand functiile de transformare geometrica (translatie sau rotatie)
 *  Pozitia sursei de lumina este modificata dupa apelarea transformarii
 *  Pozitia de vizualizare nu este modificata.
 *
 *  Se deseneaza un tor cu material de culoare gri
 *  Obiectul este iluminat de o singura sursa de lumina
 *
 *  Interactiune: prin apasarea butonului stang al mouse-ului,
 *  transformarea de modelare se modifica prin inmultirea cu matricea de rotatie cu 30 grade
 *  Scena este redesenata cu torul in noua pozitie.
 */
#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

static int spin = 10;

void CALLBACK moveLight(AUX_EVENTREC* event)
{
	spin = (spin + 20) % 360;
}

void myInit()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);
}

// Pozitia sursei de lumina este resetata dupa ce se apleleaza transformarea de rotatie. 
// Aceasta plaseaza sursa intr-o noua pozitie in coordonate reale.
// Cubul reprezinta pozitia sursei de lumina.
void CALLBACK display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(0.0, 0.0, -5.0); // pozitia de observare

	glPushMatrix();
	glRotated((GLdouble)spin, 1.0, 0.0, 0.0); // rotatia sursei

	GLfloat position[] = { 0.0, 0.0, 1.5, 1.0 }; // pozitia sursei
	glLightfv(GL_LIGHT0, GL_POSITION, position); // functie apelata
	
	// doar dupa ce s-a stabilit matricea de rotatie se deseneaza cubul corespunzand pozitiei sursei
	glTranslated(0.0, 0.0, 1.5);
	glDisable(GL_LIGHTING);
	glColor3f(0.0, 1.0, 1.0);
	auxWireCube(0.1);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	// se deseneaza torul
	auxSolidTorus(0.275, 0.85);
	glPopMatrix();

	glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_SINGLE | AUX_RGB | AUX_DEPTH16);
	auxInitPosition(0, 0, 800, 600);
	auxInitWindow("Sursa isi modifica pozitia la apasarea butonului stang al mouse-ului");
	myInit();
	auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSEDOWN, moveLight);
	auxReshapeFunc(myReshape);
	auxMainLoop(display);
	return 0;
}
