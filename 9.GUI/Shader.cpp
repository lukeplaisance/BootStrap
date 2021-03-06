#include "Shader.h"
#include <assert.h>
#include <string>
#include <stdio.h>


Shader::Shader()
{
	m_program = glCreateProgram();
}


Shader::~Shader()
{
}

void Shader::Bind()
{
	glUseProgram(m_program);
}

void Shader::UnBind()
{
	glUseProgram(0);
}

bool Shader::load(const char * filename, Shader::SHADER_TYPE shadertype)
{
	errno_t err;
	FILE *file;
	err = fopen_s(&file, filename, "r");
	char buf[500];
	while (std::fgets(buf, sizeof buf, file))
	{
		switch (shadertype)
		{
			case Shader::SHADER_TYPE::VERTEX:
				vsSourceString.append(buf);
				break;

			case Shader::SHADER_TYPE::FRAGMENT:
				fsSourceString.append(buf);
				break;
		}
	}
	fclose(file);

	switch (shadertype)
	{
		case Shader::SHADER_TYPE::FRAGMENT:
			fsSource = fsSourceString.c_str();
			break;

		case Shader::SHADER_TYPE::VERTEX:
			vsSource = vsSourceString.c_str();
			break;
	}

	return true;
}

bool Shader::attach()
{
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(m_vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(m_vertexShader);
	glShaderSource(m_fragmentShader, 1, (const char**)&fsSource, 0);
	glCompileShader(m_fragmentShader);

	glAttachShader(m_program, m_vertexShader);
	glAttachShader(m_program, m_fragmentShader);
	glLinkProgram(m_program);

	return true;
}

void Shader::defaultLoad()
{
	//Default Shaders
	vsSource = "#version 410\n \
                            layout(location = 0) in vec4 Position; \
                            layout(location = 1) in vec4 Color; \
                            out vec4 vColor; \
                            uniform mat4 ProjectionViewWorld; \
                            void main() { vColor = Color; \
                            gl_Position = ProjectionViewWorld * Position; }";

	fsSource = "#version 410\n \
                            in vec4 vColor; \
                            out vec4 FragColor; \
                            void main() { FragColor = vColor; }";
}

unsigned int Shader::getUniform(const char * name)
{
	return glGetUniformLocation(m_program, name);
}
