//
//  TextureLoader.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "TextureLoader.h"

#include <stdio.h>

TextureLoader::TextureLoader()
: mWidth(0), mHeight(0), mInternalFormat(GL_RGBA8), mImageFormat(GL_BGRA), mWrapS(GL_REPEAT), mWrapT(GL_REPEAT), mFilterMin(GL_LINEAR), mFilterMax(GL_LINEAR) {
    glGenTextures(1, &this->mID);
}

void TextureLoader::Generate(GLuint width, GLuint height, unsigned char* data)
{
    this->mWidth = width;
    this->mHeight = height;
    // Create Texture
    glBindTexture(GL_TEXTURE_2D, this->mID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->mInternalFormat, width, height, 0, this->mImageFormat, GL_UNSIGNED_BYTE, (void*) data);
    // Set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->mWrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->mWrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->mFilterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->mFilterMax);
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureLoader::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->mID);
}

