// link statically w/ GLEW
#define GLEW_STATIC

// headers
#include <GL/glew.h>
#include <SFML/Window.hpp>




// vertex shader

const char* vertexShaderSrc = R"glsl(
#version 150 core
in vec2 pos;

void main()
{
    gl_Position = vec4(pos, 0.0, 1.0);    
}
)glsl";

// fragment shader
const char*  fragmentShaderSrc =  R"glsl(
    #version 150 core
    out vec4 outColor;

    void main()
    {
        outColor = vec4(1.0,0.0,0.0,1.0);
    }

)glsl";
// shader creation helper
Gluint createShader(Glenum type, const GLchar* src){
    Gluint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    return shader;
}

int main()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 2;
    
    sf::Window window(sf::VideoMode(800,600,32),"Circle", sf::Style::Titlebar | sf::Style::Close, settings);
  
    // intialize GLEW
    glewExperiental = GL_TRUE;
    glewInit();
    
    // Compile & activate shaders
    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSrc);
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

    Gluint ShaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttacherShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // create VBO with point coordinates

    




}