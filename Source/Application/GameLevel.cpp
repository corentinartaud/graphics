//
//  GameLevel.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "GameLevel.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>

#include "LevelReader.h"

GameObject* GameLevel::Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight) {
    // Clear old data
    Platforms.clear();
    Spikes.clear();
    
    LevelData data = LevelReader::Load(file);
    Platforms = data.platforms;
    Spikes = data.spikes;
    return data.player;
}

void GameLevel::Draw(Renderer &renderer, glm::mat4 viewMatrix) {
    for (GameObject &platform : Platforms)
        platform.Draw(renderer, viewMatrix, true);
    for (GameObject &spike : Spikes)
        spike.Draw(renderer, viewMatrix, false);
}

GLboolean GameLevel::IsCompleted() {
    return GL_FALSE;
}
