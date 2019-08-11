//
//  GameEngine.hpp
//  COMP371_Framework
//

#ifndef GameEngine_h
#define GameEngine_h

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GameObject.h"

class GameEngine {
public:
    GameEngine(GameObject*, std::vector<GameObject>, std::vector<GameObject>, float, float);
    
    void Update(float dt);
    bool HitSpikes() {return hitSpikes;};
    
private:
    bool IntersectsWithPlatforms(glm::vec2);
    bool IntersectsWithSpikes(glm::vec2);
    bool TwoLinesIntersect(glm::vec2, glm::vec2, glm::vec2, glm::vec2);
    
    GameObject* player;
    std::vector<GameObject> platforms;
    std::vector<GameObject> spikes;
    float gravity, forwardVelocity;
    bool hitSpikes;
};

#endif /* GameEngine_h */
