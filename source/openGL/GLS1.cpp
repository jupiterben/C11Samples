
#include "./SDLGL.h"

class S1Draw : public RenderGL
{
public: 
    void initGL()
    {
        glEnable(GL_TEXTURE_2D);
        glClearDepth(1.0f);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_DEPTH_TEST);
        glShadeModel(GL_SMOOTH);
    }
    void drawGL()
    {
        
    }
};

int main()
{
    SDLGL sdl;
    S1Draw renderer;
    sdl.pRenderer   =  &renderer;
    sdl.run();
    return 1;
}