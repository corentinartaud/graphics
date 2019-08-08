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

void GameLevel::Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight) {
    // Clear old data
    this->Bricks.clear();
    // Load from file
    GLuint tileCode;
    GameLevel level;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<GLuint>> tileData;
    if (fstream) {
        // Read each line from level file
        while (std::getline(fstream, line)) {
            std::istringstream sstream(line);
            std::vector<GLuint> row;
            while (sstream >> tileCode) // Read each word seperated by spaces
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
            this->init(tileData, levelWidth, levelHeight);
    }
}

void GameLevel::Draw(Renderer &renderer) {
    for (GameObject &tile : this->Bricks)
        tile.Draw(renderer);
}

GLboolean GameLevel::IsCompleted() {
    return GL_FALSE;
}

void GameLevel::init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight) {
    // Calculate dimensions
    GLuint height = (GLuint) tileData.size();
    GLuint width = (GLuint) tileData[0].size(); // Note we can index vector at [0] since this function is only called if height > 0
    GLfloat unit_width = 100, unit_height = 100;
    // Initialize level tiles based on tileData
    for (GLuint y = 0; y < height; ++y) {
        for (GLuint x = 0; x < width; ++x) {
            // Check block type from level data (2D level array)
            glm::vec2 pos(unit_width * x, 0);
            glm::vec2 size(unit_width, unit_height);
            GameObject obj(pos, size, ResourceManager::GetTexture("grass"), glm::vec3(0.8f, 0.8f, 0.7f));
            this->Bricks.push_back(obj);
        }
    }
}
