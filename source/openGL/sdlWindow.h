 #pragma once

#include "renderWindow.h"

 #include <SDL2/SDL.h>
 #include <SDL2/SDL_opengl.h>

class SDLGL
{
public: 
    SDLGL()
    {  
        quit = false;
        window  = nullptr;
        init();
    }   
    ~SDLGL()
    {
        SDL_DestroyWindow(window);
        window = NULL;
        SDL_Quit();
    }

    void run()
    {
        quit = false;
        while (!quit)
        {
            SDL_Event sdlEvent;
            while(SDL_PollEvent(&sdlEvent))
            {
                if(sdlEvent.type == SDL_QUIT)
                {
                    quit = true;
                }
            }
            if(fDraw)
                fDraw();
            SDL_Delay(16);
        }       
    }
protected:
    bool quit;
    SDL_Window* window;
    SDL_GLContext glContext;

    void init()
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,32);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_Init(SDL_INIT_EVERYTHING);
        window = SDL_CreateWindow("SDL+OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,600,600,SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
        glContext = SDL_GL_CreateContext(window);
        SDL_GL_SetSwapInterval(1);
        if(fInit)
            fInit();
    }
};


//  void LoadImage()
//  {
//      SDL_Surface *tmp=IMG_Load("water.png");
//      if(tmp)
//      {
//         tmp = SDL_ConvertSurfaceFormat(tmp,SDL_PIXELFORMAT_ABGR8888,0);
//         //texture= glGenerateMipmap(GL_TEXTURE_2D,4,tmp->w,tmp->h,GL_RGBA,GL_UNSIGNED_BYTE,tmp->pixels);
//         SDL_FreeSurface(tmp);
//      }
//  }
