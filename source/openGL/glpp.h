#pragma once

#include <gl/gl.h>

namespace glpp
{
	//pipeline state
    //depth
    namespace depth
    {
        void enableTest(bool b){ b?glEnable(GL_DEPTH_TEST):glDisable(GL_DEPTH_TEST); }
        void enableWrite(bool b){ glDepthMask(b?GL_TRUE:GL_FALSE); }
        bool isEnableTest(){ return glIsEnabled(GL_DEPTH_TEST)!=0; }
        bool isEnableWrite(){ 
			GLboolean b;
			glGetBooleanv(GL_DEPTH_WRITEMASK, &b);
			return b!=0;
		}
    };    
    //resource
	

	//shader	
	class Shader
	{
	public:
		enum Type
		{
			_vertexTy = GL_VERTEX_SHADER,
			_geometryTy = GL_GEOMETRY_SHADER,
			_fragmentTy = GL_FRAGMENT_SHADER,
		};
		Shader() :handle(0) {}
		void create(Type st) { handle = glCreateShader(st);  }
		void source(const std::string& src) { 
			const GLchar *source = src.data(); 
			glShaderSource(handle, 1, &source, nullptr); 
		}
		void compile() {
			glCompileShader(handle);
		}
		void destroy() { glDeleteShader(handle);  }
		bool isCompiled()const {
			GLint isCompiled;
			glGetShaderiv(handle, GL_COMPILE_STATUS, &isCompiled);
			return isCompiled!=0;
		}
		void getInfoLog(std::string& log) {
			GLint length(0);
			glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);
			if (length > 1)
			{
				GLchar *logMessage = new GLchar[length];				
				glGetShaderInfoLog(handle, length, NULL, logMessage);
				log = logMessage;
				delete[] logMessage;
			}			
		}
	protected:
		GLuint handle;
	};
    

};