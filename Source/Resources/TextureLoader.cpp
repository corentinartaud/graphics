//
//  TextureLoader.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "TextureLoader.h"

#include <stdio.h>

TextureLoader::TextureLoader() : mWidth(0), mHeight(0) {
    glGenTextures(1, &this->mID);
}

void TextureLoader::Generate(int width, int height, unsigned char* data) {
    this->mWidth = width;
    this->mHeight = height;

    glBindTexture(GL_TEXTURE_2D, this->mID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*) data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

// Binding the texture
void TextureLoader::Bind() const {
    glBindTexture(GL_TEXTURE_2D, this->mID);
}

