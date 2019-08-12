//
//  Shader.h
//  COMP371_Project
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#ifndef Shader_h
#define Shader_h

#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

/*
General purpsoe shader loader. Compiles from file, generates compile/link-time error messages.
Hosts several utility functions for easy management of the shaders.
*/
class Shader {
public:
    // State
    GLuint mID;
    // Constructor
    Shader() { }
    // Sets the current shader as active
    Shader &Use();
    // Compiles the shader from given source code
    void Compile(const GLchar *vertexSource, const GLchar *fragmentSource);
    // Utility functions
    void SetInteger (const GLchar *name, GLint value, GLboolean useShader = false);
    void SetVector3f (const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
    void SetMatrix4 (const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);
private:
    // Checks if compilation or linking failed and if so, print the error logs
    void checkCompileErrors(GLuint object, std::string type);
};

#endif /* Shader_h */
