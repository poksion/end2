#ifdef _WIN32
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glut.h>
#elif defined(__APPLE__) || defined(__APPLE_CC__)
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
#elif defined(__ANDROID_API__)
	#include <GLES/gl.h>
#else // GLX
    #include <GL/gl.h>
    #include <GL/glu.h>
	#include <GL/glut.h>
#endif

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
