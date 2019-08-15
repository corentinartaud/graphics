//
//  ResourceManager.h
//  COMP371_Project
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#ifndef ResourceManager_h
#define ResourceManager_h

#include <map>
#include <string>

#include <GL/glew.h>

#include "TextureLoader.h"
#include "Shader.h"


/*
ResourceManager class that hosts functions to load Textures and Shaders.
Each loaded texture and/or shader is also stored for future reference by string handles.
*/
class ResourceManager {
public:
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, TextureLoader> Textures;
    // loads a shader
    static Shader LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, std::string name);
    // retrieves a shader by reference
    static Shader &GetShader(std::string name);
    // loads a texture from file
    static TextureLoader LoadTexture(const GLchar *file, std::string name);
    // retrieves a texture by reference
    static TextureLoader &GetTexture(std::string name);
    // de-allocates all
    static void Clear();
private:
    // loads and generate shader from file
    static Shader loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile);
    // loads and generate texture from file
    static TextureLoader loadTextureFromFile(const GLchar *file);
};

#endif /* ResourceManager_h */
