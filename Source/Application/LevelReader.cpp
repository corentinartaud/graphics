//
//  LevelReader.cpp
//  COMP371_Framework

#include "LevelReader.h"

#include <fstream>
#include <sstream>

#include "ResourceManager.h"

LevelData LevelReader::Load(const GLchar* file) {
    LevelData level;
    
    std::string line;
    std::ifstream fstream(file);
    if (fstream) {
        // Read each line
        while (std::getline(fstream, line)) {
            if (line.find("Player") != std::string::npos) {
                level.player = ReadPlayer(fstream);
            } else if (line.find("Ground") != std::string::npos) {
                level.objects.push_back(ReadGround(fstream));
            } else if (line.find("Platform") != std::string::npos) {
                ReadPlatforms(fstream, level.objects);
            } else {
                // Empty line
            }
        }
    }
    return level;
}

GameObject* LevelReader::ReadPlayer(std::ifstream& fstream) {
    GameObject* player = new GameObject();
    player->mTexture = ResourceManager::GetTexture("player");
    
    std::string line;
    while (true) {
        std::getline(fstream, line);
        std::istringstream sstream(line);
        std::string token1, token2;
        if (line.find("position") != std::string::npos) {
            // read "position :"
            sstream >> token1 >> token2;
            sstream >> token1 >> token2;
            player->mPosition = glm::vec2(std::stof(token1), std::stof(token2));
            player->mInitialPosition = player->mPosition;
        } else if (line.find("textureSize") != std::string::npos) {
            // read "textureSize :"
            sstream >> token1 >> token2;
            sstream >> token1 >> token2;
            player->mSize = glm::vec2(std::stof(token1), std::stof(token2));
        } else if (line.find("End") != std::string::npos) {
            break;
        } else {
            // Empty line
        }
    }
    return player;
}

GameObject LevelReader::ReadGround(std::ifstream& fstream) {
    GameObject object;
    object.mColor = glm::vec3(0.8f, 0.8f, 0.7f);
    object.mTexture = ResourceManager::GetTexture("ground");
    
    std::string line;
    while (true) {
        std::getline(fstream, line);
        std::istringstream sstream(line);
        std::string token1, token2;
        if (line.find("scale") != std::string::npos) {
            // read "scale :"
            sstream >> token1 >> token2;
            sstream >> token1 >> token2;
            glm::vec2 scale(std::stof(token1), std::stof(token2));
            object.mSize *= scale;
            object.mTextureScaling = scale;
        } else if (line.find("textureSize") != std::string::npos) {
            // read "textureSize :"
            sstream >> token1 >> token2;
            sstream >> token1 >> token2;
            object.mSize *= glm::vec2(std::stof(token1), std::stof(token2));
        } else if (line.find("End") != std::string::npos) {
            break;
        } else {
            // Empty line
        }
    }
    return object;
}

void LevelReader::ReadPlatforms(std::ifstream& fstream, std::vector<GameObject>& objects) {
    glm::vec2 size(1.f, 1.f), scale;
    TextureLoader texture = ResourceManager::GetTexture("grass");
    std::vector<GameObject> newObjects;
    
    std::string line;
    while (true) {
        std::getline(fstream, line);
        std::istringstream sstream(line);
        std::string token1, token2;
        if (line.find("position") != std::string::npos) {
            while (true) {
                std::getline(fstream, line);
                std::istringstream ss(line);
                if (line.find("}") != std::string::npos)
                    break;
                ss >> token1 >> token2;
                GameObject obj;
                obj.mPosition = glm::vec2(std::stof(token1), std::stof(token2));
                newObjects.push_back(obj);
            }
        } else if (line.find("scale") != std::string::npos) {
            // read "scale :"
            sstream >> token1 >> token2;
            sstream >> token1 >> token2;
            scale = glm::vec2(std::stof(token1), std::stof(token2));
            size *= scale;
        } else if (line.find("textureSize") != std::string::npos) {
            // read "textureSize :"
            sstream >> token1 >> token2;
            sstream >> token1 >> token2;
            size *= glm::vec2(std::stof(token1), std::stof(token2));
        } else if (line.find("End") != std::string::npos) {
            break;
        } else {
            // Empty line
        }
    }
    
    for (int i = 0; i < newObjects.size(); i++) {
        newObjects[i].mSize = size;
        newObjects[i].mTexture = texture;
        newObjects[i].mTextureScaling = scale;
        objects.push_back(newObjects[i]);
    }
}
