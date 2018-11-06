// Simple game engine
// Copyright (C) 2018 Yurii Khomiak 
// Yurii Khomiak licenses this file to you under the MIT license. 
// See the LICENSE file in the project root for more information.

#include "GLSLProgram.h"
#include "Error.h"

#include <fstream>
#include <vector>


// Compile vertex and fragment shaders
void GLSLProgram::compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath)
{
    programID_ = glCreateProgram();

    vertexShader_.createShader(ShaderType::VERTEX_SHADER);
    fragmentShader_.createShader(ShaderType::FRAGMENT_SHADER);

    vertexShader_.compile(vertexShaderFilePath);
    fragmentShader_.compile(fragmentShaderFilePath);
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
	glAttachShader(programID_, vertexShader_.ID());
	glAttachShader(programID_, fragmentShader_.ID());

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
		glDeleteShader(vertexShader_.ID());
		glDeleteShader(fragmentShader_.ID());

		const std::string errorString = errorLog.data();
		fatalError(errorString + "Shaders failed to link!");
	}

	// Detaching shaders
	glDetachShader(programID_, vertexShader_.ID());
	glDetachShader(programID_, fragmentShader_.ID());

	// Deleting shaders
	glDeleteShader(vertexShader_.ID());
	glDeleteShader(fragmentShader_.ID());
}

// Use current program
void GLSLProgram::use() const
{
	glUseProgram(programID_);

	for (int i = 0; i < numAttributes_; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

// Unuse current program
void GLSLProgram::unuse() const
{
	glUseProgram(0);

	for (int i = 0; i < numAttributes_; i++)
	{
		glDisableVertexAttribArray(i);
	}
}