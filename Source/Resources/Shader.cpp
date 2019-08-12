//
//  Shader.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "Shader.h"

#include <iostream>

Shader &Shader::Use() {
    glUseProgram(this->mID);
    return *this;
}

void Shader::Compile(const GLchar* vertexSource, const GLchar* fragmentSource) {
    GLuint sVertex, sFragment;
    // Vertex Shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "vertex");
    // Fragment Shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "fragment");
    // Shader Program
    printf("Linking Program\n");
    this->mID = glCreateProgram();
    glAttachShader(this->mID, sVertex);
    glAttachShader(this->mID, sFragment);
    glLinkProgram(this->mID);
    checkCompileErrors(this->mID, "program");
    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
}

void Shader::SetInteger(const GLchar *name, GLint value, GLboolean useShader) {
    if (useShader)
        this->Use();
    glUniform1i(glGetUniformLocation(this->mID, name), value);
}

void Shader::SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader) {
    if (useShader)
        this->Use();
    glUniform3f(glGetUniformLocation(this->mID, name), value.x, value.y, value.z);
}

void Shader::SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader) {
    if (useShader)
        this->Use();
    glUniformMatrix4fv(glGetUniformLocation(this->mID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(GLuint object, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "program") {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER: Compile-time error: Type: " << type << "\n" << infoLog << std::endl;
        }
    }
    else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER: Link-time error: Type: " << type << "\n" << infoLog << std::endl;
        }
    }
}
