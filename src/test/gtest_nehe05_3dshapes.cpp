#include <cute_end.h>

#include "../main/graphics/EGLHeaderWrapper.h"

class gtest_nehe05_3dshapes: public CuteGraphicTest {

    float rtri_;
    float rquad_;

    virtual void onCreate() {
        /* rotation angle for the triangle. */
        rtri_ = 0.0f;

        /* rotation angle for the quadrilateral. */
        rquad_ = 0.0f;

        glMatrixMode( GL_PROJECTION);
        gluPerspective(45, (float) 4.0 / 3.0, .1, 100);
    }

    virtual void onDestroy() {
    }

    virtual void onRender() {
        //
        // This code was created by Jeff Molofee '99 (ported to Linux/GLUT by Richard Campbell '99)
        //
        // If you've found this code useful, please let me know.
        //
        // Visit me at www.demonews.com/hosted/nehe
        // (email Richard Campbell at ulmont@bellsouth.net)
        //
#ifndef _MSC_VER

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();					// Reset The View

        glTranslatef(-1.5f, 0.0f, -6.0f);// Move Left 1.5 Units And Into The Screen 6.0
        glRotatef(rtri_, 0.0f, 1.0f, 0.0f);	// Rotate The Pyramid On The Y axis

        // draw a pyramid (in smooth coloring mode)
        glBegin(GL_POLYGON);				// start drawing a pyramid

        // front face of pyramid
        glColor3f(1.0f, 0.0f, 0.0f);			// Set The Color To Red
        glVertex3f(0.0f, 1.0f, 0.0f);		// Top of triangle (front)
        glColor3f(0.0f, 1.0f, 0.0f);			// Set The Color To Green
        glVertex3f(-1.0f, -1.0f, 1.0f);		// left of triangle (front)
        glColor3f(0.0f, 0.0f, 1.0f);			// Set The Color To Blue
        glVertex3f(1.0f, -1.0f, 1.0f);		// right of traingle (front)

        // right face of pyramid
        glColor3f(1.0f, 0.0f, 0.0f);			// Red
        glVertex3f(0.0f, 1.0f, 0.0f);		// Top Of Triangle (Right)
        glColor3f(0.0f, 0.0f, 1.0f);			// Blue
        glVertex3f(1.0f, -1.0f, 1.0f);		// Left Of Triangle (Right)
        glColor3f(0.0f, 1.0f, 0.0f);			// Green
        glVertex3f(1.0f, -1.0f, -1.0f);		// Right Of Triangle (Right)

        // back face of pyramid
        glColor3f(1.0f, 0.0f, 0.0f);			// Red
        glVertex3f(0.0f, 1.0f, 0.0f);		// Top Of Triangle (Back)
        glColor3f(0.0f, 1.0f, 0.0f);			// Green
        glVertex3f(1.0f, -1.0f, -1.0f);		// Left Of Triangle (Back)
        glColor3f(0.0f, 0.0f, 1.0f);			// Blue
        glVertex3f(-1.0f, -1.0f, -1.0f);		// Right Of Triangle (Back)

        // left face of pyramid.
        glColor3f(1.0f, 0.0f, 0.0f);			// Red
        glVertex3f(0.0f, 1.0f, 0.0f);		// Top Of Triangle (Left)
        glColor3f(0.0f, 0.0f, 1.0f);			// Blue
        glVertex3f(-1.0f, -1.0f, -1.0f);		// Left Of Triangle (Left)
        glColor3f(0.0f, 1.0f, 0.0f);			// Green
        glVertex3f(-1.0f, -1.0f, 1.0f);		// Right Of Triangle (Left)

        glEnd();							// Done Drawing The Pyramid

        glLoadIdentity();				// make sure we're no longer rotated.
        glTranslatef(1.5f, 0.0f, -7.0f);// Move Right 3 Units, and back into the screen 7

        glRotatef(rquad_, 1.0f, 1.0f, 1.0f);// Rotate The Cube On X, Y, and Z

        // draw a cube (6 quadrilaterals)
        glBegin(GL_QUADS);					// start drawing the cube.

        // top of cube
        glColor3f(0.0f, 1.0f, 0.0f);			// Set The Color To Blue
        glVertex3f(1.0f, 1.0f, -1.0f);		// Top Right Of The Quad (Top)
        glVertex3f(-1.0f, 1.0f, -1.0f);		// Top Left Of The Quad (Top)
        glVertex3f(-1.0f, 1.0f, 1.0f);		// Bottom Left Of The Quad (Top)
        glVertex3f(1.0f, 1.0f, 1.0f);		// Bottom Right Of The Quad (Top)

        // bottom of cube
        glColor3f(1.0f, 0.5f, 0.0f);			// Set The Color To Orange
        glVertex3f(1.0f, -1.0f, 1.0f);		// Top Right Of The Quad (Bottom)
        glVertex3f(-1.0f, -1.0f, 1.0f);		// Top Left Of The Quad (Bottom)
        glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Left Of The Quad (Bottom)
        glVertex3f(1.0f, -1.0f, -1.0f);		// Bottom Right Of The Quad (Bottom)

        // front of cube
        glColor3f(1.0f, 0.0f, 0.0f);			// Set The Color To Red
        glVertex3f(1.0f, 1.0f, 1.0f);		// Top Right Of The Quad (Front)
        glVertex3f(-1.0f, 1.0f, 1.0f);		// Top Left Of The Quad (Front)
        glVertex3f(-1.0f, -1.0f, 1.0f);		// Bottom Left Of The Quad (Front)
        glVertex3f(1.0f, -1.0f, 1.0f);		// Bottom Right Of The Quad (Front)

        // back of cube.
        glColor3f(1.0f, 1.0f, 0.0f);			// Set The Color To Yellow
        glVertex3f(1.0f, -1.0f, -1.0f);		// Top Right Of The Quad (Back)
        glVertex3f(-1.0f, -1.0f, -1.0f);		// Top Left Of The Quad (Back)
        glVertex3f(-1.0f, 1.0f, -1.0f);		// Bottom Left Of The Quad (Back)
        glVertex3f(1.0f, 1.0f, -1.0f);		// Bottom Right Of The Quad (Back)

        // left of cube
        glColor3f(0.0f, 0.0f, 1.0f);			// Blue
        glVertex3f(-1.0f, 1.0f, 1.0f);		// Top Right Of The Quad (Left)
        glVertex3f(-1.0f, 1.0f, -1.0f);		// Top Left Of The Quad (Left)
        glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Left Of The Quad (Left)
        glVertex3f(-1.0f, -1.0f, 1.0f);		// Bottom Right Of The Quad (Left)

        // Right of cube
        glColor3f(1.0f, 0.0f, 1.0f);			// Set The Color To Violet
        glVertex3f(1.0f, 1.0f, -1.0f);		// Top Right Of The Quad (Right)
        glVertex3f(1.0f, 1.0f, 1.0f);		// Top Left Of The Quad (Right)
        glVertex3f(1.0f, -1.0f, 1.0f);		// Bottom Left Of The Quad (Right)
        glVertex3f(1.0f, -1.0f, -1.0f);		// Bottom Right Of The Quad (Right)
        glEnd();							// Done Drawing The Cube

        rtri_ += 1.0f;		// Increase The Rotation Variable For The Pyramid
        rquad_ -= 1.0f;			// Decrease The Rotation Variable For The Cube
#endif
    }
};

CUTE_GRAPHIC_TEST(gtest_nehe05_3dshapes);

// vim: ts=4:sw=4
