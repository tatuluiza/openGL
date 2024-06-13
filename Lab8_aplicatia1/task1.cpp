#include "glos.h"
#include "gl.h"
#include "glu.h"
#include "glaux.h"
#include "math.h"
#include "glut.h"

GLfloat LightColor[][3] = {
    {1, 0, 0}, 
    {0, 1, 0}, 
    {0, 0, 1}  
};
int CI = 0;

float rotateX = 0.0f;
float rotateY = 0.0f;

GLfloat translateX = -199.0f;
GLfloat translateY = -100.0f;
GLfloat translateZ = -100.0f; 
GLfloat rotateAngle = 0.0f;
GLfloat moonSpeedIncrement = 0.1f;

GLfloat v[][3] = {
    {0, 1, 0},
    {1, -1, 1},
    {-1, -1, 1},
    {-1, -1, -1},
    {1, -1, -1}
};

GLint edges[][2] = {
    {0, 1},
    {0, 2},
    {0, 3},
    {0, 4},
    {1, 2},
    {2, 3},
    {3, 4},
    {4, 1},
};

GLfloat moonAngle = 0.0f;
GLfloat moonRadius = 5.0f; 
GLfloat moonSpeed = 0.5f; 

GLfloat light_position[] = { -2.0f, 2.0f, 2.0f, 1.0f };
GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; 
GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 

GLuint moonTextureID; 

GLuint incarcaTextura(const char* s) {
    GLuint textureId = 0;
    AUX_RGBImageRec* pImagineTextura = auxDIBImageLoad(s);

    if (pImagineTextura != NULL) {
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, pImagineTextura->sizeX, pImagineTextura->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pImagineTextura->data);
    }

    if (pImagineTextura) {
        if (pImagineTextura->data) {
            free(pImagineTextura->data);
        }
        free(pImagineTextura);
    }

    return textureId;
}

void initLighting() {
    glEnable(GL_LIGHTING); 
    glEnable(GL_LIGHT0); 

    // Set light source parameters
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE); 
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light_specular); 
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0f); 
}

void DrawSpaceshipBody() {
    // Main spherical body
    glColor3f(0.8, 0.6, 0.4); 
    glPushMatrix();
    glTranslatef(0.0, 0.5, 0.0);
    glScalef(1.0, 1.0, 2.0); 
    glutSolidSphere(1.0, 50, 50);
    glPopMatrix();

    // Left wing
    glColor3f(0.2, 0.2, 0.2); 
    glPushMatrix();
    glTranslatef(-1.5, 0.5, 0.0);
    glRotatef(45.0, 0.0, 1.0, 0.0); 
    glScalef(0.5, 0.2, 1.0);
    glutSolidCube(1.0); 
    glPopMatrix();

    // Right wing
    glPushMatrix();
    glTranslatef(1.5, 0.5, 0.0);
    glRotatef(-45.0, 0.0, 1.0, 0.0); 
    glScalef(0.5, 0.2, 1.0); 
    glutSolidCube(1.0); 
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0); 
    glPushMatrix();
    glTranslatef(0.0, 0.1, 0.0); 
    glScalef(1.0, 0.1, 2.0); 
    glBegin(GL_QUADS);
    glVertex3f(-0.5, 0.0, -0.5);
    glVertex3f(0.5, 0.0, -0.5); 
    glVertex3f(0.5, 0.0, 0.5); 
    glVertex3f(-0.5, 0.0, 0.5); 
    glEnd(); 
    glPopMatrix();

    glColor3f(0.5, 0.5, 0.5); 
    glPushMatrix();
    glTranslatef(0.0, 1.0, 0.0); 
    glutSolidCone(0.1, 0.6, 10, 10); 
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 1.0, 0.0); 
    glRotatef(90, 0.0, 1.0, 0.0);
    glutSolidCone(0.1, 0.6, 10, 10); 
    glPopMatrix();
}

void Move(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        translateY += 0.1f;
        break;
    case 's':
        translateY -= 0.1f;
        break;
    case 'a':
        translateX -= 0.1f;
        break;
    case 'd':
        translateX += 0.1f;
        break;
    case 'b':
        translateZ += 0.1f;
        break;
    case 'c':
        translateZ -= 0.1f;
        break;
    case 'e':
        rotateX += 5.0f;
        break;
    case 'f':
        rotateX -= 5.0f;
        break;
    case 'g':
        rotateY -= 5.0f;
        break;
    case 'h':
        rotateY += 5.0f;
        break;
    case 'p':
        moonSpeed += moonSpeedIncrement; 
        break;
    case '-':
        moonSpeed -= moonSpeedIncrement; 
        if (moonSpeed < 0) {
            moonSpeed = 0; 
        }
        break;
    }
    glutPostRedisplay();
}

void drawText(const char* text, float x, float y) {
    glRasterPos2f(x, y);
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
}

void drawMoonWithTexture() {
    glBindTexture(GL_TEXTURE_2D, moonTextureID);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glRotatef(moonAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(moonRadius, 0.0f, 0.0f);
    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluSphere(quadric, 2.0f, 40, 40);
    gluDeleteQuadric(quadric);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void drawShadow() {
    // Calcularea poziției umbrei
    GLfloat shadowProjectionMatrix[16];
    GLfloat lightPos[4] = { light_position[0], light_position[1], light_position[2], 1.0 };
    GLfloat planeCoefficients[4] = { 0, 1, 0, -3.5 }; // Planul de jos

    // Calculul matricei de proiecție ortografică pentru umbra
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.0f, -3.5f, 0.0f); // Translate to the position of the shadow
    gluLookAt(lightPos[0], lightPos[1], lightPos[2], 0, 0, 0, 0, 1, 0);
    glTranslatef(0.0f, 0.5f, 0.0f); // Translate to the position of the spaceship
    glGetFloatv(GL_MODELVIEW_MATRIX, shadowProjectionMatrix);
    glPopMatrix();

    // Desenarea umbrei
    glDisable(GL_LIGHTING);
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f); // Shadow color with alpha
    glPushMatrix();
    glMultMatrixf(shadowProjectionMatrix);
    DrawSpaceshipBody(); // Desenează umbra navei
    glPopMatrix();
    glEnable(GL_LIGHTING);
}



void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (double)w / (double)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void update(int value) {
    moonAngle += moonSpeed; 
    if (moonAngle > 360.0) {
        moonAngle -= 360.0;
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}
void initClipping() {
    GLdouble eqn[4] = { 1.0, 0.0, 0.0, 0.0 };
    glClipPlane(GL_CLIP_PLANE0, eqn);
    glEnable(GL_CLIP_PLANE0);
}




void drawBackground() {
    glColor3f(0.5f, 0.5f, 1.0f); // Setăm culoarea albastru pentru cer
    glBegin(GL_QUADS);
    glVertex3f(-10.0f, -3.5f, -10.0f);
    glVertex3f(10.0f, -3.5f, -10.0f);
    glVertex3f(10.0f, 10.0f, -10.0f);
    glVertex3f(-10.0f, 10.0f, -10.0f);
    glEnd();

}
void drawBezierCurve(GLfloat ctrlPoints[4][3], int numSegments) {
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= numSegments; ++i) {
        float t = (float)i / (float)numSegments;
        float u = 1 - t;
        float b0 = u * u * u;
        float b1 = 3 * t * u * u;
        float b2 = 3 * t * t * u;
        float b3 = t * t * t;
        float x = b0 * ctrlPoints[0][0] + b1 * ctrlPoints[1][0] + b2 * ctrlPoints[2][0] + b3 * ctrlPoints[3][0];
        float y = b0 * ctrlPoints[0][1] + b1 * ctrlPoints[1][1] + b2 * ctrlPoints[2][1] + b3 * ctrlPoints[3][1];
        float z = b0 * ctrlPoints[0][2] + b1 * ctrlPoints[1][2] + b2 * ctrlPoints[2][2] + b3 * ctrlPoints[3][2];
        glVertex3f(x, y, z);
    }
    glEnd();
}

void drawStar(GLfloat center[3], float innerRadius, float outerRadius, int numPoints) {
    GLfloat ctrlPoints[10][3] = {
        {center[0], center[1] + outerRadius, center[2]},  // Point 1 (top)
        {center[0] + innerRadius, center[1] + innerRadius, center[2]},  // Point 2 (top-right inner)
        {center[0] + outerRadius, center[1], center[2]},  // Point 3 (right)
        {center[0] + innerRadius, center[1] - innerRadius, center[2]},  // Point 4 (bottom-right inner)
        {center[0], center[1] - outerRadius, center[2]},  // Point 5 (bottom)
        {center[0] - innerRadius, center[1] - innerRadius, center[2]},  // Point 6 (bottom-left inner)
        {center[0] - outerRadius, center[1], center[2]},  // Point 7 (left)
        {center[0] - innerRadius, center[1] + innerRadius, center[2]},  // Point 8 (top-left inner)
        {center[0], center[1] + outerRadius, center[2]},  // Point 9 (top again to close the loop)
        {center[0] + innerRadius, center[1] + innerRadius, center[2]}   // Point 10 (top-right inner again)
    };

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= numPoints; ++i) {
        float t = (float)i / (float)numPoints;
        float u = 1 - t;
        float b0 = u * u * u;
        float b1 = 3 * t * u * u;
        float b2 = 3 * t * t * u;
        float b3 = t * t * t;
        float x = b0 * ctrlPoints[0][0] + b1 * ctrlPoints[1][0] + b2 * ctrlPoints[2][0] + b3 * ctrlPoints[3][0]
            + b0 * ctrlPoints[4][0] + b1 * ctrlPoints[5][0] + b2 * ctrlPoints[6][0] + b3 * ctrlPoints[7][0]
            + b0 * ctrlPoints[8][0] + b1 * ctrlPoints[9][0];
        float y = b0 * ctrlPoints[0][1] + b1 * ctrlPoints[1][1] + b2 * ctrlPoints[2][1] + b3 * ctrlPoints[3][1]
            + b0 * ctrlPoints[4][1] + b1 * ctrlPoints[5][1] + b2 * ctrlPoints[6][1] + b3 * ctrlPoints[7][1]
            + b0 * ctrlPoints[8][1] + b1 * ctrlPoints[9][1];
        float z = b0 * ctrlPoints[0][2] + b1 * ctrlPoints[1][2] + b2 * ctrlPoints[2][2] + b3 * ctrlPoints[3][2]
            + b0 * ctrlPoints[4][2] + b1 * ctrlPoints[5][2] + b2 * ctrlPoints[6][2] + b3 * ctrlPoints[7][2]
            + b0 * ctrlPoints[8][2] + b1 * ctrlPoints[9][2];
        glVertex3f(x, y, z);
    }
    glEnd();
}

void drawRainbow() {
    int numBands = 7;
    GLfloat colors[7][3] = {
        {1.0, 0.0, 0.0},    // Red
        {1.0, 0.5, 0.0},    // Orange
        {1.0, 1.0, 0.0},    // Yellow
        {0.0, 1.0, 0.0},    // Green
        {0.0, 0.0, 1.0},    // Blue
        {0.29, 0.0, 0.51},  // Indigo
        {0.56, 0.0, 1.0}    // Violet
    };

    GLfloat ctrlPoints[4][3] = {
        {-4.0, -2.0, 0.0},
        {-2.0, 2.0, 0.0},
        {2.0, 2.0, 0.0},
        {4.0, -2.0, 0.0}
    };

    for (int i = 0; i < numBands; ++i) {
        glColor3fv(colors[i]);
        drawBezierCurve(ctrlPoints, 100);
        for (int j = 0; j < 4; ++j) {
            ctrlPoints[j][1] -= 0.1;  // Offset each band slightly lower
        }
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    drawBackground();  // Desenează fundalul

    // Desenarea curcubeului în fundal
    glPushMatrix();
    glTranslatef(0.0f, -1.5f, 0.0f);  // Poziționează curcubeul sub navă
    glScalef(1.0f, 0.1f, 1.0f);       // Aplatizează curcubeul
    drawRainbow();
    glPopMatrix();



    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(rotateX, 0.0f, 1.0f, 0.0f);
    glRotatef(rotateY, 1.0f, 0.0f, 0.0f);
    DrawSpaceshipBody();

    drawMoonWithTexture();

    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(0.0f, -1.5f, 0.0f);  
    glScalef(1.0f, 0.1f, 1.0f);     
    glColor3f(0.3f, 0.3f, 0.3f);     
    DrawSpaceshipBody();
    glPopMatrix();




    drawMoonWithTexture();
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600); 
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
   
  


    glColor3f(1, 1, 1);
    drawText("Tatu Luiza-Ana", 10, 10); 

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Spaceship");
    initLighting();
   // initClipping(); /
    moonTextureID = incarcaTextura("Poza3.bmp");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(Move);
    glutTimerFunc(16, update, 0);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glutMainLoop();
    return 0;
}
