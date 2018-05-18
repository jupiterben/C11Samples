
#include <GL/glew.h>
#include "glfwWindow.h"
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "gl/gl2.h"

const char * vsSource = R"(
#version 130

precision highp float;

uniform mat4 projection_matrix;
uniform mat4 modelview_matrix;

in vec3 in_position;
in vec3 in_normal;
in vec3 in_texcoord;

out vec3 normal;
out vec3 texcoord;

void main(void)
{
  //works only for orthogonal modelview
  normal = (modelview_matrix * vec4(in_normal, 0)).xyz;
  texcoord = in_texcoord;
  gl_Position = projection_matrix * modelview_matrix * vec4(in_position, 1);    
}
)";
const char * fsSource = R"(
#version 130

precision highp float;

const vec3 ambient = vec3(0.1, 0.1, 0.1);
const vec3 lightVecNormalized = normalize(vec3(0.5, 0.5, 2.0));
const vec3 lightColor = vec3(0.9, 0.9, 0.7);

in vec3 normal;
in vec3 texcoord;

out vec4 out_frag_color;
uniform sampler2D tex1;

void main(void)
{
  float diffuse = clamp(dot(lightVecNormalized, normalize(normal)), 0.0, 1.0);
  out_frag_color = texture(tex1, vec2(texcoord.x,texcoord.y) );// vec4(ambient + diffuse * lightColor, 1.0);
}
)";

float vertexData[] = { 0,0,0, 0,1,0, 1,1,0 };


auto gl = ogl32::global();
ogl32::Program program;
ogl32::VAO vao;

void Init()
{
	gl.init();
	gl.depth.test.enable();
	gl.depth.test.setPassFunction(ogl32::_lessEqual);
	gl.depth.write.enable();
	gl.depth.calculate.setRange();
	gl.depth.calculate.offsetFill.enable();
	gl.depth.calculate.offsetLine.enable();
	gl.depth.calculate.offsetPoint.enable();
	gl.depth.calculate.setOffset(-1, -1);

	gl.depth.calculate.
	glDisable(GL_CULL_FACE);

	std::string sError;
	if (gl.getLastError(sError)) {
		return;
	}

	//gl.scissor.test.enable();
	auto r = gl.scissor.getBox();
	//gl.scissor.setBox(r);
	gl.viewport.set(r);
	//build shader
	auto vs = gl.createVertexShader()
		.setSource(vsSource)
		.compile();
	
	auto fs = gl.createFragmentShader()
		.setSource(fsSource)
		.compile();

	program = gl.createProgram()
		   .attach(vs).attach(fs)
		   .link();

	if (!program.isLinked())
	{
		std::string sInfo = program.getInfoLog();
		std::cout << sInfo << std::endl;
	}
	
	//
	auto vbo = gl.createVBO();
	if (vbo) {
		gl.bufferTarget.array.bind(vbo)
			.setData(vertexData, sizeof(vertexData))
			.unbind();
	}

	vao = gl.createVAO();
	if (vao)
	{
		vao.bind();
		gl.bufferTarget.array.bind(vbo);
		vao.setAttributeData(program.attribute("gVertex"), VAO::_3, VAO::_float, false, 0, 0);
		vao.unBind();
	}

}
void Draw()
{	
	glClear(GL_COLOR_BUFFER_BIT);

	glm::mat4 prjMat;
	
	auto activeProg = gl.useProgram(program);
	activeProg.setUniform("model", prjMat);
	activeProg.setUniform("model", prjMat);

	vao.bind();
	gl.drawArray(3);
	vao.unBind();
	
}


int main(void)
{
    glfwWindow glfwin;

	glfwin.OnInit = Init;
	glfwin.OnDraw = Draw;
   
    glfwin.run();
}