/*
 * Programul demonstreaza utilizarea modelului de iluminare GL.
 * Sunt desenate mai multe sfere cu caracteristici de material diferite. O singura sursa de lumina ilumineaza obiectele.
 */
#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

void myInit(void)
{
	// componenta ambientala din sursa 0 este lumina cu intensitate 0
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	// componenta difuza din sursa 0 este lumina cu intensitate 1 pentru fiecare componenta de culoare R, G, B
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// sursa 0 este la infinit pe directia y=3, z=2
	GLfloat position[] = { 0.0, 3.0, 2.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	GLfloat local_view[] = { 0.0 };
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

	glEnable(GL_LIGHTING); // activare iluminare
	glEnable(GL_LIGHT0); // activare sursa 0

	glClearColor(0.0, 0.1, 0.1, 0.0); // culoare cyan 

	glEnable(GL_DEPTH_TEST); // activare test de adancime
	glDepthFunc(GL_LESS); // modelul de comparatie in testul de adancime
}

/*  Deseneaza 12 sfere pe 3 randuri si patru coloane
 *  Sferele din primul rand au materiale fara coeficient de reflexie
 *  Sferele din al doilea rand au materiale cu coeficient de reflexie semnificativ
 *  Sferele din al treilea rand au materiale cu coeficient de reflexie colorat
 *
 *  Prima coloana are materiale doar cu coeficient de reflexie difuza, albastra.
 *  A doua coloana, pe langa coeficientul de reflexie difuza albastru are si reflexie speculara cu exponent mic
 *  A treia coloana, pe langa coeficientul de reflexie difuza albastru are si reflexie speculara cu exponent mare
 *  A patra coloana are materiale care includ si componenta emisiva (materiale flourescente)
 *
 *  glTranslatef() este utilizata pentru plasarea sferelor in pozitia dorita
 */
void CALLBACK display()
{
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 }; // coeficient de reflexie ambientala
	GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
	GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 }; // coeficient de reflexie difuza
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };//coeficient de reflexie speculara
	GLfloat no_shininess[] = { 0.0 }; // exponentul de reflexie speculara
	GLfloat low_shininess[] = { 5.0 }; // exponentul de reflexie speculara
	GLfloat high_shininess[] = { 100.0 }; // exponentul de reflexie speculara
	GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 }; // intensitatea luminii emise

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// draw sphere in first row, first column diffuse reflection only; no ambient or specular
	glPushMatrix();
	glTranslatef(-3.75, 3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	auxSolidSphere(1.0);
	glPopMatrix();

	//  draw sphere in first row, second column diffuse and specular reflection; low shininess; no ambient
	glPushMatrix();
	glTranslatef(-1.25, 3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	auxSolidSphere(1.0);
	glPopMatrix();

	// draw sphere in first row, third column diffuse and specular reflection; high shininess; no ambient
	glPushMatrix();
	glTranslatef(1.25, 3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	auxSolidSphere(1.0);
	glPopMatrix();

	// draw sphere in first row, fourth column diffuse reflection; emission; no ambient or specular reflection
	glPushMatrix();
	glTranslatef(3.75, 3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	auxSolidSphere(1.0);
	glPopMatrix();

	// draw sphere in second row, first column ambient and diffuse reflection; no specular
	glPushMatrix();
	glTranslatef(-3.75, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	auxSolidSphere(1.0);
	glPopMatrix();

	// draw sphere in second row, second column ambient, diffuse and specular reflection; low shininess
	glPushMatrix();
	glTranslatef(-1.25, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	auxSolidSphere(1.0);
	glPopMatrix();

	// draw sphere in second row, third column ambient, diffuse and specular reflection; high shininess
	glPushMatrix();
	glTranslatef(1.25, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	auxSolidSphere(1.0);
	glPopMatrix();

	// draw sphere in second row, fourth column ambient and diffuse reflection; emission; no specular
	glPushMatrix();
	glTranslatef(3.75, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	auxSolidSphere(1.0);
	glPopMatrix();

	// draw sphere in third row, first column colored ambient and diffuse reflection; no specular
	glPushMatrix();
	glTranslatef(-3.75, -3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	auxSolidSphere(1.0);
	glPopMatrix();

	// draw sphere in third row, second column colored ambient, diffuse and specular reflection; low shininess
	glPushMatrix();
	glTranslatef(-1.25, -3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	auxSolidSphere(1.0);
	glPopMatrix();

	// draw sphere in third row, third column colored ambient, diffuse and specular reflection; high shininess
	glPushMatrix();
	glTranslatef(1.25, -3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	auxSolidSphere(1.0);
	glPopMatrix();

	// draw sphere in third row, fourth column colored ambient and diffuse reflection; emission; no specular
	glPushMatrix();
	glTranslatef(3.75, -3.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	auxSolidSphere(1.0);
	glPopMatrix();

	glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= (h * 2)) {
		glOrtho(-6.0, 6.0, -3.0 * ((GLfloat)h * 2) / (GLfloat)w, 3.0 * ((GLfloat)h * 2) / (GLfloat)w, -10.0, 10.0);
	}
	else {
		glOrtho(-6.0 * (GLfloat)w / ((GLfloat)h * 2), 6.0 * (GLfloat)w / ((GLfloat)h * 2), -3.0, 3.0, -10.0, 10.0);
	}
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_SINGLE | AUX_RGB | AUX_DEPTH16);
	auxInitPosition(0, 0, 600, 450);
	auxInitWindow("Sfere cu coeficienti pentru reflexia ambientala, stralucire si emisivitate diferite");
	myInit();
	auxReshapeFunc(myReshape);
	auxMainLoop(display);
	return 0;
}
