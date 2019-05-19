#include <stdlib.h>
#include <GLUT/GLUT.h>
#include <string>
#include <cmath>
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
//общее
int Width = 1280;
int Height = 640;
int i;
//график и с ним связанное
int a = -15;
int b = 15;
int Scale = 40;
double Density=0.0001;
bool DensEnable=true;
//функции
double Function;
double x;
double y;

void reshape (int Width, int Height){
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
    glOrtho(0, Width , 0, Height, -5, 5);
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

void drawAxes(){
    //
    // ОСИ
    //
    glBegin(GL_LINES);
    glVertex2i(0, Height/2);
    glVertex2i(Width, Height/2);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(Width/2, 0);
    glVertex2i(Width/2, Height);
    glEnd();
    
    //
    // Рисочки
    //
    glBegin(GL_LINES);
    for (i=-Width/2; i<=Width/2; i+=Scale){
        glVertex2i(Width/2+i, Height/2-5);// нижняя правая
        glVertex2i(Width/2+i, Height/2+5);   //нижняя левая
    }
    glEnd();
    glBegin(GL_LINES);
    for (i=-Height/2; i<=Height/2; i+=Scale){
        glVertex2i(Width/2-5, Height/2+i);// нижняя правая
        glVertex2i(Width/2+5, Height/2+i);   //нижняя левая
    }
    glEnd();
}

void drawFunc(int dens){
    glPointSize(3);
    glBegin(GL_POINTS);
    //Density=0.0001;
    for (x=-Width/2; x<=Width/2; x+=Density){
        //y=sqrt(x)*sqrt(10-x); //Потемка
        y=pow(2,((2*x*x)-x-2));    //Серебрякова
        glVertex2i((Width/2)+x*Scale,(Height/2)+y*Scale);
    }
    glEnable(GL_POINT_SMOOTH);
    glEnd();
}

void drawScale(int Scale){
    //Горизонт
    for (int i=a; i<=b; i++){
        int spacing;
        std::string text;
        text =std::to_string(i);
        if (i<=0) {
            spacing=15;
        } else{
            spacing=5;
        }
        drawText(text.data(), 3,Width/2+(i*Scale)-spacing,Height/2-25);
    }
    //Вертик
    for (int i=a; i<=b; i++){
        int spacing;
        std::string text;
        text =std::to_string(i);
        if (i<=0) {
            spacing=5;
        } else{
            spacing=5;
        }
        if (i!=0){
            drawText(text.data(), 3,Width/2+15,Height/2+(i*Scale)-spacing);
        }
    //Обознач
        drawText("X", 1, Width-15, Height/2);
        drawText("Y", 1, Width/2-15, Height-35);
    }
}

void density (){
    if (DensEnable){
        Density=0.0001;
    } else {
        Density=1.0;
    }
}

void display()
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.42, 1.44);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    //Рисуем оси
    drawAxes();
    drawScale(Scale);
    //Рисуем функцию
    
    drawFunc(15);
    glutSwapBuffers();
    glFinish();
}

void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN){
        switch (button){
            case GLUT_LEFT_BUTTON:
                DensEnable = true;
                break;
            case GLUT_RIGHT_BUTTON:
                DensEnable = false;
                break;
        }
        glutPostRedisplay();
    }
}

int main (int argc, char * argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(1280, 640);
    glutCreateWindow("OpenGL pt.5");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
