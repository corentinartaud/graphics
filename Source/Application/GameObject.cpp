//
//  GameObject.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "GameObject.h"

GameObject::GameObject()
: mInitialPosition(0.0f, 0.0f), mPosition(0.f, 0.f), mSize(1.f, 1.f), mVelocity(0.0f, 0.0f), mColor(1.0f), mRotation(0.0f), mTexture(), mTextureScaling(1.0f, 1.0f) { }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, TextureLoader texture, glm::vec3 color, glm::vec2 velocity)
: mPosition(pos), mSize(size), mVelocity(velocity), mColor(color), mRotation(180.0f), mTexture(texture) { }

void GameObject::Draw(Renderer &renderer, glm::mat4 viewMatrix) {
    renderer.Render(this->mTexture, this->mPosition, this->mSize, this->mRotation, this->mColor, this->mTextureScaling, viewMatrix);
}

