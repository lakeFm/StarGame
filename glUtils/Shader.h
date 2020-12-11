#ifndef STARGAME_SHADER_H
#define STARGAME_SHADER_H

#include "../core/shortCalls.h"
#include <fstream>
#include <sstream>
#include <iostream>

class Shader{
private:
    GLuint ID;
public:    
    Shader(C char* vertexPath, C char* fragmentPath)
    {
        string vertexCode;
        string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            vShaderFile.close();
            fShaderFile.close();
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        unsigned int vertex, fragment;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        glDeleteShader(vertex);
        glDeleteShader(fragment);

    }
    
    fun use() C{glUseProgram(ID);}
    fun setBool(C std::string& name, bool value) C{
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    fun setInt(C std::string& name, int value) C{
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    fun setFloat(C std::string& name, float value) C{
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    fun setVec2(C std::string& name, C  vec2 &value) C{
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    fun setVec2(C std::string& name, float x, float y) C{
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }
    fun setVec3(C std::string& name, C  vec3 &value) C{
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    fun setVec3(C std::string& name, float x, float y, float z) C{
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
      
    fun setVec4(C std::string& name, C  vec4 &value) C{
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    fun setVec4(C std::string& name, float x, float y, float z, float w) C{
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }
      
    fun setMat2(C std::string& name, C  mat2 &mat) C{
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
      
    fun setMat3(C std::string& name, C  mat3 &mat) C{
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
      
    fun setMat4(C std::string& name, C  mat4 &mat) C{
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    GLuint getProgram() {ret ID;}
    GLuint getProgram()C{ret ID;}

private:
      
    fun checkCompileErrors(GLuint shader, string type)
    {
        GLuint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, reinterpret_cast<GLint *>(&success));
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, reinterpret_cast<GLint *>(&success));
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};

#endif //STARGAME_SHADER_H
