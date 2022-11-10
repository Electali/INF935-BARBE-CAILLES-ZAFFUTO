#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>

#include "../maths/matrix44.hpp"

using namespace std;

/**
 * @brief Classe Shader,
 */
class Shader
{
public:
    ////////////////////////
    //// Constructeurs. ////
    ////////////////////////

    /**
     * @brief Construit un nouveau Shader.
     */
    Shader()
    {
        const char *vertexShaderSource = "#version 330 core\n"
                                         "layout (location = 0) in vec3 aPos;\n"
                                         "uniform mat4 model;\n"
                                         "uniform mat4 view;\n"
                                         "uniform mat4 projection;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   gl_Position = projection * view * model*vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                         "}\0";

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        const char *fragmentShaderSource = "#version 330 core\n"
                                           "out vec4 FragColor;\n"
                                           "uniform vec4 color;\n"
                                           "void main()\n"
                                           "{\n"
                                           "FragColor = color;\n"
                                           "}\0";

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);

        program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

        glUseProgram(program);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

public:
    ////////////////////////////////////////////////////////////
    //// Envoie de Donnée au Shader sur la Carte Graphique. ////
    ////////////////////////////////////////////////////////////

    void setUniform(const string& name, const vec4& vec)
    {
        glUseProgram(program);
        glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, vec);
    }

    /**
     * @brief Envoie d'une Matrice4x4 de type float à l'Uniform correspondant.
     * 
     * @param name Nom de l'Uniform sur le Shader.
     * @param mat Matrice4x4 de type float à envoyer.
     */
    void setUniform(const string& name, const mat4& mat) const
    {
        glUseProgram(program);
        glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, mat);
    }

    /**
     * @brief Envoie d'une Matrice4x4 de type float à l'Uniform correspondant.
     * 
     * @param name Nom de l'Uniform sur le Shader.
     * @param mat Matrice4x4 de type float à envoyer.
     */
    void setUniform(const string& name, const glm::mat4 mat) const
    {
        glUseProgram(program);
        glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    }

private:
    //////////////////
    //// Membres. ////
    //////////////////

    unsigned int program; //=> la valeur d'état machine donnée par OpenGL de notre Shader.
};

#endif // SHADER_HPP