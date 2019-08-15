//
//  GameObject.h
//  COMP371_Project
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#ifndef GameObject_h
#define GameObject_h

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "TextureLoader.h"
#include "Renderer.h"

/*
 Container object for holding all state relevant for a single game object.
*/
class GameObject {
public:
    // Object state
    glm::vec2 mInitialPosition, mPosition, mSize, mVelocity, mTextureScaling;
    glm::vec4 mColor;
    GLfloat mRotation;
    // render state
    TextureLoader mTexture;
    // Constructor(s)
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, TextureLoader texture, glm::vec4 color = glm::vec4(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

    virtual void Draw(Renderer &renderer, glm::mat4 viewMatrix = glm::mat4(1.f), bool quad = true);
};

#endif /* GameObject_h */
