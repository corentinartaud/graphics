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
    this->Bricks.clear();
    
    LevelData data = LevelReader::Load(file);
    Bricks = data.objects;
    return data.player;
}

void GameLevel::Draw(Renderer &renderer, glm::mat4 viewMatrix) {
    for (GameObject &tile : this->Bricks)
        tile.Draw(renderer, viewMatrix);
}

GLboolean GameLevel::IsCompleted() {
    return GL_FALSE;
}
