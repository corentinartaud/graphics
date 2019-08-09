//
//  LevelReader.hpp
//  COMP371_Framework

#ifndef LevelReader_h
#define LevelReader_h

#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "GameObject.h"

struct LevelData {
    GameObject* player;
    std::vector<GameObject> objects;
};

class LevelReader {
public:
    static LevelData Load(const GLchar*);
    
private:
    static GameObject* ReadPlayer(std::ifstream&);
    static GameObject ReadGround(std::ifstream&);
    static void ReadPlatforms(std::ifstream&, std::vector<GameObject>&);
};

#endif /* LevelReader_h */
