#include <stdlib.h>
#define GLUT_DISABLE_ATEXIT_HACK
#define GL_SILENCE_DEPRECATION
#include <GLUT/GLUT.h>
#include <math.h>

void draw_coordinate()
{
    glBegin(GL_LINES);
    glVertex2f(-5000, 0.0);
    glVertex2f(5000, 0.0);
    
    glVertex2f(0.0, -5000);
    glVertex2f(0.0, 5000);
    glEnd();
}

void Ellipsepot(int x0,int y0,int x, int y,int k)
{
    int m=y+y0;
    glVertex2i(x+x0,k*m);
    glVertex2i(x0-x,k*m);
}

void DDA(double a,double b,double c,int k)//k判断正负
{
    double d =a- 0.5;
    int x = 0;
    int y = 0;
    int x0= -b/2/a;
    int y0=c-b*b/4/a;
    Ellipsepot(x0,y0,x,y,k);
    glBegin(GL_POINTS);
    glVertex2i(x, floor(y + 0.5));
    while (2*a*x<=1)//斜率<=1
    {
        if (d > 0)
        {
            d += 2*a*x+3*a-1;
            ++y;
        }
        else
        {
            d += 2*a*x+3*a;
        }
        Ellipsepot(x0,y0,x,y,k);
        ++x;
    }
    while (y <500)
    {
        if (d > 0)
        {
            d +=-1;
        }
        else
        {
            d +=2*a*x+2*a-1;
            ++x;
        }
        Ellipsepot(x0,y0,x,y,k);
        ++y;
    }
    glEnd();
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h); //它负责把视景体截取的场景按照怎样的高和宽显示到屏幕上。
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(left, right, bottom, top, near, far)负责使用什么样的视景体来截取场景
    gluOrtho2D(-0.5 * w, 0.5 * w, -0.5 * h, 0.5 * h);
    //glOrtho(0.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
    glClearColor(1.f, 1.f, 1.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //绘制图形
    glColor3f(0.0f, 0.0f, 1.0f);
    draw_coordinate();
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(2.0);
    
    DDA(0.005,2,100,-1);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(240, 240);
    glutCreateWindow(argv[0]);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
