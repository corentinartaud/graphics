//
//  GameEngine.cpp
//  COMP371_Framework
//

#include "GameEngine.h"

#include <iostream>
using namespace std;

GameEngine::GameEngine() { }

GameEngine::GameEngine(GameObject* p, std::vector<GameObject> v, float g, float fv)
: player(p), platforms(v), gravity(g), forwardVelocity(fv) {}

void GameEngine::Update(float dt) {
    // Update the player velocity
    player->mVelocity.x = forwardVelocity;
    player->mVelocity.y += gravity * dt;
    
    glm::vec2 newPos = player->mPosition + player->mVelocity * dt;
    // Check if new X position is valid
    if (!IntersectsWithPlatforms(glm::vec2(newPos.x, player->mPosition.y)))
        player->mPosition.x = newPos.x;
    else
        player->mVelocity.x = 0.f;

    if (!IntersectsWithPlatforms(glm::vec2(player->mPosition.x, newPos.y)))
        player->mPosition.y = newPos.y;
    else
        player->mVelocity.y = 0.f;
}

bool GameEngine::IntersectsWithPlatforms(glm::vec2 pos) {
    // AABB testing against all platforms
    for (auto platform: platforms) {
        if ((pos.x < platform.mPosition.x + platform.mSize.x) &&
            (pos.x + player->mSize.x > platform.mPosition.x) &&
            (pos.y + player->mSize.y > platform.mPosition.y) &&
            (pos.y < platform.mPosition.y + platform.mSize.y))
            return true;
    }
    return false;
}
