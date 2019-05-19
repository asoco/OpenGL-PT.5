#include <stdlib.h>
#include <GLUT/GLUT.h>
#include <string>
#include <cmath>
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

int Width = 1280;
int Height = 640;
int Density = 40;
int i=0;

void reshape (int Width, int Height)
{
    glViewport(0, 0, Width, Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, Width, 0, Height); // задаем область видимости (слева, справа, снизу, сверху)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawText(const char *text, int length, int x, int y){
    glMatrixMode(GL_PROJECTION);
    double *matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0, 800 , 0, 600, -5, 5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x,y);
    for(int i=0; i<length; i++){
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
    }
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}

void drawFunc(int dens){
    double x;
    double y;
    glPointSize(2);
    glBegin(GL_POINTS);
    for (x=-Width/2; x<=Width/2; x+=0.0001){
        y = sqrt(x)*sqrt(10-x);
        glVertex2i((Width/2)+x*40,(Height/2)+y*40);
    }
    glEnable(GL_POINT_SMOOTH);
    glEnd();
}

void display()
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.42, 1.44);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    //Рисуем оси
    glBegin(GL_LINES);
        glVertex2i(0, Height/2);     // ОСЬ
        glVertex2i(Width, Height/2);  // Х
    glEnd();
    glBegin(GL_LINES);
        glVertex2i(Width/2, 0);// нижняя правая
        glVertex2i(Width/2, Height);   //нижняя левая
    glEnd();

    //
    //Деления
    //
    glBegin(GL_LINES);
        for (i=-Width/2; i<=Width/2; i+=Density){
            glVertex2i(Width/2+i, Height/2-5);// нижняя правая
            glVertex2i(Width/2+i, Height/2+5);   //нижняя левая
        }
    glEnd();
    glBegin(GL_LINES);
        for (i=-Height/2; i<=Height/2; i+=Density){
            glVertex2i(Width/2-5, Height/2+i);// нижняя правая
            glVertex2i(Width/2+5, Height/2+i);   //нижняя левая
        }
    glEnd();
    
    drawFunc(15);
    glutSwapBuffers();
}
int main (int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1280, 640);
    glutCreateWindow("OpenGL pt.5");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    
    //glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}


/*
 //
 // ПОДПИСИ
 // не работают
 for (int i=-17; i<=17; i++){
 std::string text;
 text =std::to_string(i);
 glColor3i(255, 0, 255);
 //for (int j=-Width/2; j<=Width/2; j+=Density){
 drawText(text.data(), 2, Width/2+i,Height/2-35);
 //}
 }
 */

