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
It hosts basic utility functions for easy management of textures.
*/
class TextureLoader {
public:
    // Holds the ID of the texture object, used for all texture operations to reference to this particlar texture
    GLuint mID;
    // Texture image dimensions
    GLuint mWidth, mHeight; // Width and height of loaded image in pixels
    // Texture Format
    GLuint mInternalFormat; // Format of texture object
    GLuint mImageFormat; // Format of loaded image
    // Texture configuration
    GLuint mWrapS; // Wrapping mode on S axis
    GLuint mWrapT; // Wrapping mode on T axis
    GLuint mFilterMin; // Filtering mode if texture pixels < screen pixels
    GLuint mFilterMax; // Filtering mode if texture pixels > screen pixels
    
    // Constructor (sets default texture modes)
    TextureLoader();
    
    // Generates texture from image data
    void Generate(GLuint width, GLuint height, unsigned char* data);
    
    // Binds the texture as the current active GL_TEXTURE_2D texture object
    void Bind() const;
};

#endif /* TextureLoader_h */
