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
 General purpose shader loader. Compiles from file, generates compile/link-time error messages.
 Hosts several utility functions for easy management of the shaders.
*/
class Shader {
public:
    // State
    GLuint mID;
    // Sets the current shader as active
    Shader &Use();
    // Compiles the shader from given source code
    void Compile(const char *vertexSource, const char *fragmentSource);
    // Utility functions
    void SetInteger (const char *name, int value, bool useShader = false);
    void SetVector3f (const char *name, const glm::vec3 &value, bool useShader = false);
    void SetVector4f (const char *name, const glm::vec4 &value, bool useShader = false);
    void SetMatrix4 (const char *name, const glm::mat4 &matrix, bool useShader = false);
private:
    // Checks if compilation or linking failed and if so, print the error logs
    void checkCompileErrors(int object, std::string type);
};

#endif /* Shader_h */
