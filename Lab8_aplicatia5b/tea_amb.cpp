/*
 *  Programul afiseaza trei cesti de ceai, cu aceeasi sursa de lumina
 *  dar cu diferite valori pentru coeficientii de reflexie pentru lumina ambientala
 */
#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

void myInit()
{
	// setari pentru sursa de lumina
	// intensitatea componentei ambientale din sursa 0 este nula
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	// intensitatea componentei difuze din sursa 0 este maxima pentru fiecare componenta de culoare
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	// intensitatea componentei speculare din sursa 0 este maxima pentru fiecrae compopnenta de culoare
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	// pozitia sursei de lumina nu este cea implicita
	GLfloat light_position[] = { 1.0, 0.0, 0.0, 0.0 };
	// sursa de lumina pe axa x la infinit
	GLfloat global_ambient[] = { 0.75, 0.75, 0.75, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// lumina ambientala in scena
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);


	glFrontFace(GL_CW); // orientarea implicita a varfurilor in sensul rotirii acelor
	glEnable(GL_LIGHTING); // activare iluminare
	glEnable(GL_LIGHT0); // activare sursa 0

	glEnable(GL_AUTO_NORMAL); // activare calculare normale daca varfurile s-au determinat cu GL_MAP2_VERTEX_3 sau GL_MAP2_VERTEX_4
	glEnable(GL_NORMALIZE); // activare normalizare (vectori unitari) vectori

	glEnable(GL_DEPTH_TEST); // activare test adancime
}

void CALLBACK display()
{
	GLfloat low_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat more_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat most_ambient[] = { 1.0, 1.0, 1.0, 1.0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// coeficient de reflexie pentru lumina ambientala mic
	glMaterialfv(GL_FRONT, GL_AMBIENT, low_ambient);
	glMaterialf(GL_FRONT, GL_SHININESS, 40.0);
	glPushMatrix();
	glTranslatef(0.0, 2.0, 0.0);
	auxSolidTeapot(1.0);
	glPopMatrix();

	// coeficient de reflexie pentru lumina ambientala mediu
	glMaterialfv(GL_FRONT, GL_AMBIENT, more_ambient);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	auxSolidTeapot(1.0);
	glPopMatrix();

	// coeficient de reflexie pentru lumina ambientala mare
	glMaterialfv(GL_FRONT, GL_AMBIENT, most_ambient);
	glPushMatrix();
	glTranslatef(0.0, -2.0, 0.0);
	auxSolidTeapot(1.0);
	glPopMatrix();
	glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho(-4.0, 4.0, -4.0 * (GLfloat)h / (GLfloat)w, 4.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	}
	else {
		glOrtho(-4.0 * (GLfloat)w / (GLfloat)h, 4.0 * (GLfloat)w / (GLfloat)h, -4.0, 4.0, -10.0, 10.0);
	}
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_SINGLE | AUX_RGB | AUX_DEPTH16);
	auxInitPosition(0, 0, 800, 800);
	auxInitWindow("Iluminarea ambientala pentru materiale cu coeficienti de reflexie diferiti");
	myInit();
	auxReshapeFunc(myReshape);
	auxMainLoop(display);
	return 0;
}
