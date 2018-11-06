// Simple game engine
// Copyright (C) 2018 Yurii Khomiak 
// Yurii Khomiak licenses this file to you under the MIT license. 
// See the LICENSE file in the project root for more information.

#ifndef SHADER_H_
#define SHADER_H_

#include <GL/glew.h>
#include <string>


enum class ShaderType { VERTEX_SHADER, FRAGMENT_SHADER };


class Shader
{
public:
    Shader() = default;
    
    void createShader(ShaderType shaderType);
    void compile(const std::string &shaderFilePath);

    GLuint ID() const noexcept
    {
        return shaderID_;
    }

private:
    GLuint shaderID_{ 0 };

    const std::string getShaderContent(const std::string &shaderFilePath) const;

    void checkCompilationError(const std::string &shaderFilePath);
};


#endif // SHADER_H_

