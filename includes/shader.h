//
// Created by sam on 2020-07-18.
//

#ifndef SDF_SHADER_H
#define SDF_SHADER_H


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader {
public:
    Shader() = default;

    // Constructor generates the shader on the fly
    Shader(const GLchar *vertexPath, const GLchar *fragmentPath) {
        // Retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // Ensures ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::badbit);
        try {
            // Open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // Read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // Close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // Convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure &e) {
            std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
        }
        const GLchar *vShaderCode = vertexCode.c_str();
        const GLchar *fShaderCode = fragmentCode.c_str();
        // Compile shaders
        GLuint vertex, fragment;
        GLint success;
        GLchar infoLog[512];
        // Vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        // Print compile errors if any
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // Fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        // Print compile errors if any
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // Shader Program
        this->program = glCreateProgram();
        glAttachShader(this->program, vertex);
        glAttachShader(this->program, fragment);
        glLinkProgram(this->program);
        // Print linking errors if any
        glGetProgramiv(this->program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(this->program, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        // Delete the shaders as they're linked into our program
        glDeleteShader(vertex);
        glDeleteShader(fragment);

    }

    // Uses the current shader
    void use() const {
        glUseProgram(this->program);
    }

    // Set uniform value
    void setBool(const std::string &name, GLboolean value) const {
        glUniform1i(glGetUniformLocation(this->program, name.c_str()), (GLint) value);
    }

    void setInt(const std::string &name, GLint value) const {
        glUniform1i(glGetUniformLocation(this->program, name.c_str()), value);
    }

    void setFloat(const std::string &name, GLfloat value) const {
        glUniform1f(glGetUniformLocation(this->program, name.c_str()), value);
    }

    void setVec2(const std::string &name, const glm::vec2 &value) const {
        glUniform2fv(glGetUniformLocation(this->program, name.c_str()), 1, &value[0]);
    }

    void setVec2(const std::string &name, GLfloat x, GLfloat y) const {
        glUniform2f(glGetUniformLocation(this->program, name.c_str()), x, y);
    }

    void setVec3(const std::string &name, const glm::vec3 &value) const {
        glUniform3fv(glGetUniformLocation(this->program, name.c_str()), 1, &value[0]);
    }

    void setVec3(const std::string &name, GLfloat x, GLfloat y, GLfloat z) const {
        glUniform3f(glGetUniformLocation(this->program, name.c_str()), x, y, z);
    }

    void setVec4(const std::string &name, const glm::vec4 &value) const {
        glUniform4fv(glGetUniformLocation(this->program, name.c_str()), 1, &value[0]);
    }

    void setVec4(const std::string &name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const {
        glUniform4f(glGetUniformLocation(this->program, name.c_str()), x, y, z, w);
    }

    void setMat2(const std::string &name, const glm::mat2 &mat) const {
        glUniformMatrix2fv(glGetUniformLocation(this->program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat3(const std::string &name, const glm::mat3 &mat) const {
        glUniformMatrix3fv(glGetUniformLocation(this->program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat4(const std::string &name, const glm::mat4 &mat) const {
        glUniformMatrix4fv(glGetUniformLocation(this->program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    GLuint program;
};


#endif //SDF_SHADER_H
