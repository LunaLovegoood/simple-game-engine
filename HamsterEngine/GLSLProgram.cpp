// Simple game engine
// Copyright (C) 2018 Yurii Khomiak 
// Yurii Khomiak licenses this file to you under the MIT license. 
// See the LICENSE file in the project root for more information.

#include "GLSLProgram.h"
#include "Error.h"

#include <fstream>
#include <vector>

GLSLProgram::~GLSLProgram()
{

}


// Compile vertex and fragment shaders
void GLSLProgram::compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath)
{
	createShaders();

	programID_ = glCreateProgram();

	compileShader(vertexShaderFilePath, vertexShaderID_);
	compileShader(fragmentShaderFilePath, fragmentShaderID_);
}

// Create vertex and fragment shaders
void GLSLProgram::createShaders()
{
	// Create vertex shader
	vertexShaderID_ = glCreateShader(GL_VERTEX_SHADER);
	if (!vertexShaderID_)
	{
		fatalError("Vertex shader failed to be created!");
	}

	// Create fragment shader
	fragmentShaderID_ = glCreateShader(GL_FRAGMENT_SHADER);
	if (!vertexShaderID_)
	{
		fatalError("Fragment shader failed to be created!");
	}
}

// Compile shader from given path
void GLSLProgram::compileShader(const std::string &shaderFilePath, GLuint shaderID)
{
	auto shaderContent = getShaderContent(shaderFilePath); // contains shader contents

	// Load shader
	const char* shaderContentArr = shaderContent.c_str();
	glShaderSource(shaderID, 1, &shaderContentArr, nullptr);

	// Compile shader
	glCompileShader(shaderID);

	// Check if the compilation was successful
	GLint isCompiled = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		// Get error log
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

		// Free resources
		glDeleteShader(shaderID);

		fatalError(errorLog[0] + "\nShader: " + shaderFilePath + " failed to compile!");

		return;
	}
}

// Returns shader program contents
const std::string GLSLProgram::getShaderContent(const std::string &shaderFilePath)
{
	// Open shader file
	std::ifstream shaderFile(shaderFilePath);
	if (shaderFile.fail())
	{
		fatalError("Failed to open " + shaderFilePath);
	}

	// Get file size
	shaderFile.seekg(0, std::ios::end);

	size_t fileSize = shaderFile.tellg();

	shaderFile.seekg(0, std::ios::beg);

	// Create string to hold file contents and reserve space for file size
	std::string shaderContents(fileSize, ' ');

	// Get shader program content
	shaderFile.read(&shaderContents[0], fileSize);

	shaderFile.close();

	return shaderContents;
}

// Bind attributes location
void GLSLProgram::addAttribute(const std::string &attributeName)
{
	glBindAttribLocation(programID_, numAttributes_++, attributeName.c_str());
}

// Link vertex and fragment shaders
void GLSLProgram::linkShaders()
{
	// Attach shaders to program
	glAttachShader(programID_, vertexShaderID_);
	glAttachShader(programID_, fragmentShaderID_);

	// Link program
	glLinkProgram(programID_);

	// Check if the shaders were successfuly linked
	GLint isLinked = 0;
	glGetProgramiv(programID_, GL_LINK_STATUS, (int *)&isLinked);

	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(programID_, GL_INFO_LOG_LENGTH, &maxLength);

		// Get error log
		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(programID_, maxLength, &maxLength, &errorLog[0]);

		// Clean up shaders and program
		glDeleteProgram(programID_);
		glDeleteShader(vertexShaderID_);
		glDeleteShader(fragmentShaderID_);

		fatalError(errorLog[0] + "\nShaders: failed to link!");

		return;
	}

	// Detaching shaders
	glDetachShader(programID_, vertexShaderID_);
	glDetachShader(programID_, fragmentShaderID_);

	// Deleting shaders
	glDeleteShader(vertexShaderID_);
	glDeleteShader(fragmentShaderID_);
}

// Use current program
void GLSLProgram::use()
{
	glUseProgram(programID_);

	for (int i = 0; i < numAttributes_; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

// Unuse current program
void GLSLProgram::unuse()
{
	glUseProgram(0);

	for (int i = 0; i < numAttributes_; i++)
	{
		glDisableVertexAttribArray(i);
	}
}