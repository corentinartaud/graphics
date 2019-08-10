//
//  GameLevel.h
//  COMP371_Project
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#ifndef GameLevel_h
#define GameLevel_h

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"


class GameLevel {
public:
    // Level state
    std::vector<GameObject> Bricks;
    // Constructor
    GameLevel() { }
    // Loads level from file, returns player
    GameObject* Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight);
    // Render level
    void Draw(Renderer &renderer, glm::mat4 viewMatrix);
    // Check if the level is completed (all non-solid tiles are destroyed)
    GLboolean IsCompleted();
};

#endif /* GameLevel_h */
