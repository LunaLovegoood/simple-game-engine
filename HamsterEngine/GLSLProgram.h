// Simple game engine
// Copyright (C) 2018 Yurii Khomiak 
// Yurii Khomiak licenses this file to you under the MIT license. 
// See the LICENSE file in the project root for more information.

#ifndef GLSLPROGRAM_H_
#define GLSLPROGRAM_H_

#include "Shader.h"

#include <GL/glew.h>
#include <string>


// Provides operations with shaders
class GLSLProgram
{
public:
	GLSLProgram() = default;
	~GLSLProgram() = default;

	void compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);

	void linkShaders();

	void addAttribute(const std::string &attributeName);

	void use() const;
	void unuse() const;

private:
	GLuint programID_{ 0 };

    Shader vertexShader_{};
    Shader fragmentShader_{};

	int numAttributes_{};
};


#endif // GLSLPROGRAM_H_