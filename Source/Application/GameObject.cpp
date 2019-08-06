//
//  GameObject.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "GameObject.h"

GameObject::GameObject()
: mPosition(0, 0), mSize(1, 1), mVelocity(2.0f, 2.0f), mGravity(0.0f, -2.0f), mColor(1.0f), mRotation(0.0f), mTexture() { }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, TextureLoader texture, glm::vec3 color, glm::vec2 velocity, glm::vec2 gravity)
: mPosition(pos), mSize(size), mVelocity(velocity), mGravity(gravity), mColor(color), mRotation(180.0f), mTexture(texture) { }

void GameObject::Draw(Renderer &renderer) {
    renderer.Render(this->mTexture, this->mPosition, this->mSize, this->mRotation, this->mColor);
}

