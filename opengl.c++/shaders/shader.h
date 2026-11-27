// Shader helper in the style of LearnOpenGL's shader.h.
// Loads vertex + fragment (+ optional geometry) shaders from files, compiles,
// links, and reports errors. Requires glad to be included/loaded first.
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    unsigned int ID;

    // geometryPath is optional: pass a path to enable a geometry shader
    // (e.g. for the explode effect).
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
    {
        std::string vertexCode   = readFile(vertexPath);
        std::string fragmentCode = readFile(fragmentPath);
        std::string geometryCode = geometryPath ? readFile(geometryPath) : "";

        unsigned int vertex   = compile(GL_VERTEX_SHADER,   vertexCode.c_str(),   "VERTEX");
        unsigned int fragment = compile(GL_FRAGMENT_SHADER, fragmentCode.c_str(), "FRAGMENT");
        unsigned int geometry = 0;
        if (geometryPath)
            geometry = compile(GL_GEOMETRY_SHADER, geometryCode.c_str(), "GEOMETRY");

        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        if (geometryPath)
            glAttachShader(ID, geometry);
        glLinkProgram(ID);
        checkErrors(ID, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if (geometryPath)
            glDeleteShader(geometry);
    }

    void use() const { glUseProgram(ID); }

    // uniform setters
    void setBool (const std::string& name, bool value)  const { glUniform1i(loc(name), (int)value); }
    void setInt  (const std::string& name, int value)   const { glUniform1i(loc(name), value); }
    void setFloat(const std::string& name, float value) const { glUniform1f(loc(name), value); }
    void setVec2 (const std::string& name, const glm::vec2& v) const { glUniform2fv(loc(name), 1, &v[0]); }
    void setVec2 (const std::string& name, float x, float y) const { glUniform2f(loc(name), x, y); }
    void setVec3 (const std::string& name, const glm::vec3& v) const { glUniform3fv(loc(name), 1, &v[0]); }
    void setVec3 (const std::string& name, float x, float y, float z) const { glUniform3f(loc(name), x, y, z); }
    void setVec4 (const std::string& name, const glm::vec4& v) const { glUniform4fv(loc(name), 1, &v[0]); }
    void setVec4 (const std::string& name, float x, float y, float z, float w) const { glUniform4f(loc(name), x, y, z, w); }
    void setMat2 (const std::string& name, const glm::mat2& m) const { glUniformMatrix2fv(loc(name), 1, GL_FALSE, &m[0][0]); }
    void setMat3 (const std::string& name, const glm::mat3& m) const { glUniformMatrix3fv(loc(name), 1, GL_FALSE, &m[0][0]); }
    void setMat4 (const std::string& name, const glm::mat4& m) const { glUniformMatrix4fv(loc(name), 1, GL_FALSE, &m[0][0]); }

private:
    int loc(const std::string& name) const { return glGetUniformLocation(ID, name.c_str()); }

    static std::string readFile(const char* path)
    {
        std::ifstream file(path);
        if (!file)
        {
            std::cerr << "ERROR::SHADER::FILE_NOT_READ: " << path << std::endl;
            return "";
        }
        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    static unsigned int compile(GLenum type, const char* src, const std::string& label)
    {
        unsigned int shader = glCreateShader(type);
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);
        checkErrors(shader, label);
        return shader;
    }

    static void checkErrors(unsigned int object, const std::string& type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(object, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(object, 1024, nullptr, infoLog);
                std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
            }
        }
        else
        {
            glGetProgramiv(object, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(object, 1024, nullptr, infoLog);
                std::cerr << "ERROR::PROGRAM_LINKING_ERROR\n" << infoLog << std::endl;
            }
        }
    }
};

#endif
