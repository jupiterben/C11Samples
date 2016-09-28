#include "gl/glew.h"
#include "glfwWindow.h"
int main(void)
{
    glfwWindow w;

    w.fInit = []()
    {
        glewInit();
        glEnable(GL_TEXTURE_2D);
        glClearDepth(1.0f);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_DEPTH_TEST);
        glShadeModel(GL_SMOOTH);
    };

    w.fDraw = []()
    {
        glBegin(GL_TRIANGLES);
        glVertex3d(1,1,0);
        glVertex3d(1,0,0);
        glVertex3d(0,1,0);
        glEnd();
    };
   
    w.run();
}