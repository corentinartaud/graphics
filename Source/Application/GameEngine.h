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
    GameEngine();
    GameEngine(GameObject*, std::vector<GameObject>, float, float);
    
    void Update(float dt);
    
private:
    bool IntersectsWithPlatforms(glm::vec2);
    
    GameObject* player;
    std::vector<GameObject> platforms;
    float gravity, forwardVelocity;
};

#endif /* GameEngine_h */
