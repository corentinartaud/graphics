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
A static singleton ResourceManager class that hosts several functions to load Textures and Shaders.
Each loaded texture and/or shader is also stored for future reference by string handles.
All functions and resources are static and no public constructor is defined.
*/
class ResourceManager {
public:
    // Resource storage
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, TextureLoader> Textures;
    // Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
    static Shader LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, std::string name);
    // Retrieves a stored shader by reference
    static Shader &GetShader(std::string name);
    // Loads (and generates) a texture from file
    static TextureLoader LoadTexture(const GLchar *file, GLboolean alpha, std::string name);
    // Retrieves a stored texture by reference
    static TextureLoader &GetTexture(std::string name);
    // Properly de-allocates all loaded resources
    static void Clear();
    
    static ResourceManager* GetInstance() { return instance; };
private:
    // Private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
    ResourceManager() { }
    // Loads and generates a shader from file
    static Shader loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile);
    // Loads a single texture from file
    static TextureLoader loadTextureFromFile(const GLchar *file, GLboolean alpha);
    
    static ResourceManager* instance;
};

#endif /* ResourceManager_h */
