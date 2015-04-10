#include <cute_end.h>

#include <iostream>
#include <vector>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

class gtest_glut : public CuteGraphicTest {
public:

    virtual void onCreate(){
        glMatrixMode( GL_PROJECTION);
        gluPerspective(45, (float) 4.0 / 3.0, .1, 100);
    }

    virtual void onRender(){
        // Z angle
        static float angle = 0;

        // model view
        glMatrixMode( GL_MODELVIEW);

        // Load identity matrix
        glLoadIdentity();
        // Multiply in translation matrix
        glTranslatef(0, 0, -10);
        // Multiply in rotation matrix
        glRotatef(angle, 0, 0, 1);
        // Render colored quad
        glBegin( GL_QUADS);
        glColor3ub(255, 000, 000);
        glVertex2f(1, 1);
        glColor3ub(000, 255, 000);
        glVertex2f(-1, 1);
        glColor3ub(000, 000, 255);
        glVertex2f(-1, -1);
        glColor3ub(255, 255, 000);
        glVertex2f(1, -1);
        glEnd();

        // Increase angle to rotate
        angle += 0.25;
    }
    virtual void onDestroy(){

    }
};

CUTE_GRAPHIC_TEST(gtest_glut);
