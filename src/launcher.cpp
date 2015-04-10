#include <cute_end.h>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "main/graphics/EGraphicContextOpenGL.h"
#include "main/modules/ELogModule.h"
#include "main/modules/EMouseModule.h"
#include "main/modules/EKeyboardModule.h"
#include "main/modules/EKeyboardModuleGlut.h"

#include "main/system/ESystem.h"

// Unit test or graphic test
static bool GRAPHIC_TEST = true;
static CuteGraphicTest* graphicTest;
static cute::suite* filteredUnitTestSuite;

void setupTestConfiguration(int argc, char** argv){

    // 1. Current graphic test (a.k.a gt_)
    GRAPHIC_TEST = true;
    filteredUnitTestSuite = 0;
    //graphicTest = CuteSuite::get_graphic_suite()["gtest_glut"];
    //graphicTest = CuteSuite::get_graphic_suite()["gtest_nehe05_3dshapes"];
    graphicTest = CuteSuite::get_graphic_suite()["gtest_geometrybuffer"];

    // 2. All unit tests
//    GRAPHIC_TEST = false;
//    graphicTest = 0;
//    filteredUnitTestSuite = 0;

    // 3. Filtered unit tests
//    GRAPHIC_TEST = false;
//    graphicTest = 0;
//    filteredUnitTestSuite = new cute::suite();
//    cute::suite& suite = CuteSuite::get_suite();
//    for(auto itr = suite.begin(); itr != suite.end(); ++itr){
//        if(itr->name() == "test_matrix"){
//            filteredUnitTestSuite->push_back(*itr);
//        }
//    }

}

class GraphicContextOpenGLDelegate : public end2::EGraphicContextOpenGL::Delegate {
public:
    GraphicContextOpenGLDelegate(){}
    virtual ~GraphicContextOpenGLDelegate(){}

    virtual void flip(){
        glutSwapBuffers();
    }
} myOpenGLContextDelegate;


// OpenGL Main loop
void main_loop_function() {
    end2::EGraphicContext* gc = end2::ESystem::getSystem().getModule<end2::EGraphicContext>();
    gc->clearBuffers();
    if(gc->beginDrawing()) {
        if(graphicTest != 0){
            graphicTest->onRender();
        }
    }
    gc->endDrawing();
    gc->flip();
}

void key_down_function(unsigned char key, int x, int y){
    end2::EKeyboardModule* km = end2::ESystem::getSystem().getModule<end2::EKeyboardModule>();
    km->updateKeyState(key, true);
}

void key_up_function(unsigned char key, int x, int y){
    end2::EKeyboardModule* km = end2::ESystem::getSystem().getModule<end2::EKeyboardModule>();
    km->updateKeyState(key, false);
}

void key_special_down_function(int key, int x, int y){
    end2::EKeyboardModule* km = end2::ESystem::getSystem().getModule<end2::EKeyboardModule>();
    km->updateKeyState(key, true);
}

void key_special_up_function(int key, int x, int y){
    end2::EKeyboardModule* km = end2::ESystem::getSystem().getModule<end2::EKeyboardModule>();
    km->updateKeyState(key, false);
}

int main(int argc, char** argv) {

    // test configuration
    setupTestConfiguration(argc, argv);

    // create system
    end2::ESystem::newSystem();

    if (GRAPHIC_TEST) {

        int window_width = 800;
        int window_height = 600;

        // create window
        glutInit(&argc, argv);
        glutInitWindowSize(window_width, window_height);
        glutInitDisplayMode(GLUT_RGBA|GLUT_ALPHA|GLUT_DOUBLE|GLUT_DEPTH);
        glutCreateWindow("end2 graphic test");

        // create modules
        end2::ESystem::getSystem().createModule<end2::ELogModule>();
        end2::ESystem::getSystem().createModule<end2::EMouseModule>();
        end2::ESystem::getSystem().createModule<end2::EKeyboardModuleGlut, end2::EKeyboardModule>();

        // create graphic context
        end2::EGraphicContextOpenGL* openGLContext = end2::ESystem::getSystem().createModule<end2::EGraphicContextOpenGL, end2::EGraphicContext>();

        // setup graphic context
        openGLContext->setDelegate(&myOpenGLContextDelegate);
        openGLContext->init();
        openGLContext->setDisplaySize(window_width, window_height);

        // set graphic test
        if(graphicTest != 0){
            graphicTest->onCreate();
        }

        // main loop
        glutDisplayFunc(main_loop_function);
        glutIdleFunc(main_loop_function);
        //glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping

        glutKeyboardFunc(key_down_function);
        glutKeyboardUpFunc(key_up_function);
        glutSpecialFunc(key_special_down_function);
        glutSpecialUpFunc(key_special_up_function);

        glutMainLoop();

        // halt graphic context
        openGLContext->halt();

    } else {

        if(filteredUnitTestSuite != 0){
            CuteSuite::run_suite(*filteredUnitTestSuite);
            delete filteredUnitTestSuite;
        }else{
            // run unit test suite
            CuteSuite::run_suite();
        }
    }

    // set graphic test
    if(graphicTest != 0){
        graphicTest->onDestroy();
    }

    // halt system
    end2::ESystem::getSystem().clearModules();
    end2::ESystem::deleteSystem();

    return 0;
}

