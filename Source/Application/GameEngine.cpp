//
//  GameEngine.cpp
//  COMP371_Framework
//

#include "GameEngine.h"

#include <iostream>
using namespace std;

GameEngine::GameEngine(GameObject* p, std::vector<GameObject> v, std::vector<GameObject> s, float g, float fv)
: player(p), platforms(v), spikes(s), gravity(g), forwardVelocity(fv), hitSpikes(false) {}

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
    
    hitSpikes = IntersectsWithSpikes(player->mPosition);
}

bool GameEngine::IntersectsWithPlatforms(glm::vec2 pos) {
    // AABB testing against all platforms
    for (auto &platform: platforms) {
        if ((pos.x < platform.mPosition.x + platform.mSize.x) &&
            (pos.x + player->mSize.x > platform.mPosition.x) &&
            (pos.y + player->mSize.y > platform.mPosition.y) &&
            (pos.y < platform.mPosition.y + platform.mSize.y))
            return true;
    }
    return false;
}

bool GameEngine::IntersectsWithSpikes(glm::vec2 pos) {
    glm::vec2 playerCoordinates[] = {
        pos,
        pos + glm::vec2(player->mSize.x, 0.f),
        pos + player->mSize,
        pos + glm::vec2(0.f, player->mSize.y)
    };
    for (auto &spike: spikes) {
        glm::vec2 spikeCoordiantes[] = {
            spike.mPosition,
            spike.mPosition + glm::vec2(spike.mSize.x, 0.f),
            spike.mPosition + glm::vec2(spike.mSize.x / 2.f, spike.mSize.y)
        };
        
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 3; j++)
                if (TwoLinesIntersect(playerCoordinates[i],
                                      playerCoordinates[(i + 1) % 4],
                                      spikeCoordiantes[j],
                                      spikeCoordiantes[(j + 1) % 3]))
                    return true;
    }
    return false;
}

// a1 and a2 are the line 1 start and end
// b1 and b2 are the line 2 start and end
bool GameEngine::TwoLinesIntersect(glm::vec2 a1, glm::vec2 a2, glm::vec2 b1, glm::vec2 b2) {
    glm::vec2 line1 = a2 - a1;
    glm::vec2 line2 = b2 - b1;
    float dotProd = line1.x * line2.y - line1.y * line2.x;
    if (dotProd == 0)
        return false;
    
    glm::vec2 line3 = b1 - a1;
    float t1 = (line3.x * line2.y - line3.y * line2.x) / dotProd;
    float t2 = (line3.x * line1.y - line3.y * line1.x) / dotProd;
    if (t1 > 0 and t1 < 1 and t2 > 0 and t2 < 1)
        return true;
    return false;
}
