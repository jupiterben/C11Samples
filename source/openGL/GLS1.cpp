
#include <GL/glew.h>
#include "glfwWindow.h"
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "glpp.h"


const char * vShader = R"(

)";
const char * pShader = R"(


)";

class Vertex
{
public:
    Vertex(std::initializer_list<GLfloat> l){

    }
    
protected:   
	GLfloat xyz[3];
    GLfloat offset[2];
};

std::vector<Vertex> vertex = {
	{ 0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0 },
	{ 0,0,0,0,0,1,1 },
	{ 0,0,0,0,0,0,1 },
};

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

      
    };
   
    w.run();
}