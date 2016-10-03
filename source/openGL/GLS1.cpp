
#include <gl/glew.h>
#include "glfwWindow.h"
#include <glm/glm.hpp>
#include <rapidjson/rapidjson.h>
#include <iostream>

#define STRINGRIFY(x) #x
char* strjson = STRINGRIFY(
    #include "scenen.json"
);

int main(void)
{
    glfwWindow w;

    w.fInit = []()
    {
        glewInit();
        glClearDepth(1.0f);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_DEPTH_TEST);
        glShadeModel(GL_SMOOTH);
    };

    w.fDraw = []()
    {
        glBegin(GL_TRIANGLES);
            glVertex3d(0.5,0.5,0);
            glVertex3d(0.5,0,0);
            glVertex3d(0,0.5,0);
        glEnd();
    };
   
    std::cout<< strjson << std::endl;

    w.run();
}