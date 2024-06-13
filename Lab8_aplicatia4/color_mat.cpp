/*
 *  Dupa initializare programul va fi in modul ColorMaterial
 *  Apasarea tastelor R, G, B va conduce la modificarea culorilor pentru reflexia difuza.
 */
#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"


GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };

void myInit()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // coeficientul de reflexie speculara
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 }; // directia sursei de lumina, aflate la infinit

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 25.0); // exponentul pentru reflexia speculara
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING); // activare model de iluminare Phong
	glEnable(GL_LIGHT0); // activare sursa 0
	glEnable(GL_DEPTH_TEST); // activare ascunderea suprafetelor
	
	glColorMaterial(GL_FRONT, GL_DIFFUSE); // culoarea data de coeficientul de reflexie difuza
	
	glEnable(GL_COLOR_MATERIAL); // urmareste culoarea curenta
}

void CALLBACK changeRedDiffuse()
{	
	// modifica componenta rosie a coeficientului de reflexie al materialului
	diffuseMaterial[0] += 0.1;
	if (diffuseMaterial[0] > 1.0) {
		diffuseMaterial[0] = 0.0;
	}
	glColor4fv(diffuseMaterial);
}

void CALLBACK changeGreenDiffuse()
{	
	// modifica componenta verde a coeficientului de reflexie al materialului
	diffuseMaterial[1] += 0.1;
	if (diffuseMaterial[1] > 1.0) {
		diffuseMaterial[1] = 0.0;
	}
	glColor4fv(diffuseMaterial);
}

void CALLBACK changeBlueDiffuse()
{	
	// modifica componenta albastra a coeficientului de reflexie al materialului
	diffuseMaterial[2] += 0.1;
	if (diffuseMaterial[2] > 1.0) {
		diffuseMaterial[2] = 0.0;
	}
	glColor4fv(diffuseMaterial);
}

void CALLBACK display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	auxSolidSphere(1.0);
	glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w, 1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	}
	else {
		glOrtho(-1.5 * (GLfloat)w / (GLfloat)h, 1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
	}
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_SINGLE | AUX_RGB | AUX_DEPTH16);
	auxInitPosition(0, 0, 800, 600);
	auxInitWindow("Modul ColorMaterial");
	myInit();
	auxKeyFunc(AUX_R, changeRedDiffuse);
	auxKeyFunc(AUX_r, changeRedDiffuse);
	auxKeyFunc(AUX_G, changeGreenDiffuse);
	auxKeyFunc(AUX_g, changeGreenDiffuse);
	auxKeyFunc(AUX_B, changeBlueDiffuse);
	auxKeyFunc(AUX_b, changeBlueDiffuse);
	auxReshapeFunc(myReshape);
	auxMainLoop(display);
	return 0;
}
