//
//  TextureLoader.h
//  COMP371_Project
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#ifndef TextureLoader_h
#define TextureLoader_h

#include <GL/glew.h>

/*
 TextureLoader stores and configures a texture in OpenGL.
*/
class TextureLoader {
public:
    // constructor (sets default texture modes)
    TextureLoader();
    
    // textures id
    GLuint mID;
    
    // generates texture from image data
    void Generate(int width, int height, unsigned char* data);
    
    // binds the texture as the current active GL_TEXTURE_2D texture object
    void Bind() const;

private:
    // texture image dimensions
    int mWidth, mHeight; // width and height of loaded image in pixels
};

#endif /* TextureLoader_h */
