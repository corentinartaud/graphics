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
    std::vector<GameObject> platforms;
    std::vector<GameObject> spikes;
};

class LevelReader {
public:
    static LevelData Load(const GLchar*);
    
private:
    static GameObject* ReadPlayer(std::ifstream&);
    static GameObject ReadGround(std::ifstream&);
    static void ReadObjects(std::ifstream&, std::vector<GameObject>&, TextureLoader texture);
    // Adds spike individuals instead of spike groups defined with "scale: X.0 1.0" (X > 1)
    static void PopulateSpikes(std::vector<GameObject>&);
};

#endif /* LevelReader_h */
