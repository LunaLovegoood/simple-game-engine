#ifndef GLSLPROGRAM_H_
#define GLSLPROGRAM_H_

#include <GL/glew.h>
#include <string>

class GLSLProgram
{
public:
	void compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);

	void linkShaders();

private:
	GLuint programID_{ 0 };

	GLuint vertexShaderID_{ 0 };
	GLuint fragmentShaderID_{ 0 };
};


#endif // GLSLPROGRAM_H_