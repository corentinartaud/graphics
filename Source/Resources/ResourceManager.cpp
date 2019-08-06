//
//  ResourceManager.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <FreeImageIO.h>

// Instantiate static variables
std::map<std::string, TextureLoader> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;


Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name) {
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader &ResourceManager::GetShader(std::string name) {
    return Shaders[name];
}

TextureLoader ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name) {
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

TextureLoader &ResourceManager::GetTexture(std::string name) {
    return Textures[name];
}

void ResourceManager::Clear() {
    // (Properly) delete all shaders
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.mID);
    // (Properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.mID);
}

Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile) {
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    
    try {
        // Open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // If geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr) {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    } catch (std::exception e) {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    
    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();
    const GLchar *gShaderCode = geometryCode.c_str();
    
    // 2. Now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

TextureLoader ResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha) {
    // Create Texture object
    TextureLoader texture;
    
    // Load image using the Free Image library
    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(file, 0);
    FIBITMAP* image = FreeImage_Load(format, file);
    FIBITMAP* image32bits = FreeImage_ConvertTo32Bits(image);
    
    // Load image
    int width = FreeImage_GetWidth(image32bits);
    int height = FreeImage_GetHeight(image32bits);
    // Now generate texture
    texture.Generate(width, height, FreeImage_GetBits(image32bits));
    
    // And finally free image data
    FreeImage_Unload(image);
    FreeImage_Unload(image32bits);
    return texture;
}
