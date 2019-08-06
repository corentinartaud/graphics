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

// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject {
public:
    // Object state
    glm::vec2   mPosition, mSize, mVelocity, mGravity;
    glm::vec3   mColor;
    GLfloat     mRotation;
    // Render state
    TextureLoader   mTexture;
    // Constructor(s)
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, TextureLoader texture, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(2.0f, 2.0f), glm::vec2 gravity = glm::vec2(0.0f, -0.2f));
    // Draw sprite
    virtual void Draw(Renderer &renderer);
};

#endif /* GameObject_h */
