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
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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