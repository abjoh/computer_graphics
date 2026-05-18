#include <windows.h>
#include <GL/glut.h>
#include <math.h>

// ================= GLOBAL =================
float carX = -80;
float birdX = -80;
bool isDay = true;

// ================= CIRCLE =================
void drawCircle(float x, float y, float r)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        float a = 2 * 3.1416 * i / 100;
        glVertex2f(x + cos(a) * r, y + sin(a) * r);
    }
    glEnd();
}

// ================= SKY =================
void drawSky()
{
    if (isDay) glColor3f(0.5, 0.8, 1.0);
    else glColor3f(0.05, 0.05, 0.2);

    glBegin(GL_POLYGON);
    glVertex2f(-100,100);
    glVertex2f(100,100);
    glVertex2f(100,0);
    glVertex2f(-100,0);
    glEnd();
}

// ================= SUN/MOON =================
void drawSunMoon()
{
    if (isDay) glColor3f(1,1,0);
    else glColor3f(1,1,1);

    drawCircle(70,70,10);
}

// ================= BUILDINGS =================
void drawBuildings()
{
    // Main Building
    glColor3f(0.3,0.3,0.7);
    glBegin(GL_POLYGON);
    glVertex2f(-80,0);
    glVertex2f(-40,0);
    glVertex2f(-40,70);
    glVertex2f(-80,70);
    glEnd();

    // Windows
    glColor3f(1,1,0);
    for(int y=10; y<60; y+=15)
    {
        for(int x=-75; x<-45; x+=10)
        {
            glBegin(GL_POLYGON);
            glVertex2f(x,y);
            glVertex2f(x+5,y);
            glVertex2f(x+5,y+8);
            glVertex2f(x,y+8);
            glEnd();
        }
    }

    // Second Building
    glColor3f(0.6,0.3,0.3);
    glBegin(GL_POLYGON);
    glVertex2f(-30,0);
    glVertex2f(10,0);
    glVertex2f(10,60);
    glVertex2f(-30,60);
    glEnd();
}

// ================= TREE =================
void drawTree(float x)
{
    // trunk
    glColor3f(0.4,0.2,0);
    glBegin(GL_POLYGON);
    glVertex2f(x-2,0);
    glVertex2f(x+2,0);
    glVertex2f(x+2,15);
    glVertex2f(x-2,15);
    glEnd();

    // leaves
    glColor3f(0,0.6,0);
    drawCircle(x,20,8);
}

// ================= TRAFFIC LIGHT =================
void drawTrafficLight(float x)
{
    // pole
    glColor3f(0.2,0.2,0.2);
    glBegin(GL_POLYGON);
    glVertex2f(x-1,0);
    glVertex2f(x+1,0);
    glVertex2f(x+1,25);
    glVertex2f(x-1,25);
    glEnd();

    // lights
    glColor3f(1,0,0);
    drawCircle(x,22,2);

    glColor3f(1,1,0);
    drawCircle(x,17,2);

    glColor3f(0,1,0);
    drawCircle(x,12,2);
}

// ================= ROAD =================
void drawRoad()
{
    glColor3f(0.2,0.2,0.2);

    glBegin(GL_POLYGON);
    glVertex2f(-100,0);
    glVertex2f(100,0);
    glVertex2f(100,-50);
    glVertex2f(-100,-50);
    glEnd();
}

// ================= CAR =================
void drawCar()
{
    glColor3f(0.8,0.1,0.1);
    glBegin(GL_POLYGON);
    glVertex2f(carX-20,-5);
    glVertex2f(carX+20,-5);
    glVertex2f(carX+25,5);
    glVertex2f(carX-25,5);
    glEnd();

    glColor3f(0.9,0.2,0.2);
    glBegin(GL_POLYGON);
    glVertex2f(carX-10,5);
    glVertex2f(carX+10,5);
    glVertex2f(carX+5,15);
    glVertex2f(carX-5,15);
    glEnd();

    glColor3f(0,0,0);
    drawCircle(carX-12,-7,5);
    drawCircle(carX+12,-7,5);
}

// ================= BIRDS =================
void drawBird(float x,float y)
{
    glColor3f(0,0,0);
    drawCircle(x,y,2);

    glBegin(GL_TRIANGLES);
    glVertex2f(x,y);
    glVertex2f(x-6,y+3);
    glVertex2f(x-2,y);
    glVertex2f(x,y);
    glVertex2f(x+6,y+3);
    glVertex2f(x+2,y);
    glEnd();
}

void drawBirds()
{
    drawBird(birdX,70);
    drawBird(birdX+20,75);
    drawBird(birdX-20,72);
}

// ================= DISPLAY =================
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawSky();
    drawSunMoon();
    drawBuildings();

    drawTree(30);
    drawTree(50);

    drawTrafficLight(0);

    drawRoad();
    drawCar();
    drawBirds();

    glFlush();
}

// ================= UPDATE =================
void update(int v)
{
    carX += 0.8;
    if(carX > 100) carX = -100;

    birdX += 1.2;
    if(birdX > 100) birdX = -100;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// ================= KEYBOARD =================
void keyboard(unsigned char key,int x,int y)
{
    if(key==' ')
        isDay = !isDay;
}

// ================= RESHAPE =================
void reshape(int w,int h)
{
    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100,100,-100,100);

    glMatrixMode(GL_MODELVIEW);
}

// ================= INIT =================
void init()
{
    glClearColor(1,1,1,1);
}

// ================= MAIN =================
int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(800,600);
    glutCreateWindow("City Scene");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutTimerFunc(0,update,0);

    glutMainLoop();
}
