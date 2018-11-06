#include "Shader.h"
#include "Error.h"

#include <fstream>
#include <vector>


void Shader::createShader(ShaderType shaderType)
{
    std::string errorString{};

    switch (shaderType)
    {
    case ShaderType::VERTEX_SHADER:
        shaderID_ = glCreateShader(GL_VERTEX_SHADER);
        errorString += "Vertex ";
        break;

    case ShaderType::FRAGMENT_SHADER:
        shaderID_ = glCreateShader(GL_FRAGMENT_SHADER);
        errorString += "Fragment ";
        break;
    }

    if (!shaderID_)
    {
        errorString += "shader failed to be created!";

        fatalError(errorString);
    }
}

// Compile shader
void Shader::compile(const std::string &shaderFilePath)
{
    if (!shaderID_)
    {
        fatalError("Shader wasn't created");
    }

    const std::string shaderContent = getShaderContent(shaderFilePath); // contains shader contents

    // Load shader
    const char* ptrShaderContent = shaderContent.c_str();
    glShaderSource(shaderID_, 1, &ptrShaderContent, nullptr);

    glCompileShader(shaderID_);

    checkCompilationError(shaderFilePath);
}

// Returns shader program contents
const std::string Shader::getShaderContent(const std::string &shaderFilePath) const
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

// Check if the compilation was successful
void Shader::checkCompilationError(const std::string &shaderFilePath)
{
    // Check if the compilation was successful
    GLint isCompiled = 0;
    glGetShaderiv(shaderID_, GL_COMPILE_STATUS, &isCompiled);

    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shaderID_, GL_INFO_LOG_LENGTH, &maxLength);

        // Get error log
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shaderID_, maxLength, &maxLength, &errorLog[0]);

        // Free resources
        glDeleteShader(shaderID_);

        const std::string errorString = errorLog.data();
        fatalError(errorString + "Shader: " + shaderFilePath + " failed to compile!");
    }
}

