#pragma once

#include "renderWindow.h"
#include <GLFW/glfw3.h>

class glfwWindow : public RenderWindow
{
public:
    glfwWindow():window(nullptr)
    {
        init();
    }
    int init()
    {
        /* Initialize the library */
        if (!glfwInit())
            return -1;

         glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
         glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
         glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
         glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
         glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }
        return 0;
    }
    void run()
    {
        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        if(fInit)
            fInit();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        { 

            if(fDraw)
                fDraw();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    ~glfwWindow()
    {
         glfwTerminate();
    }

protected:
    GLFWwindow* window;

};