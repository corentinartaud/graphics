//
//  Game.h
//  COMP371_Project
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include <array>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GameLevel.h"

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100, 100);
// Initial velocity of the player paddle
const GLfloat PLAYER_VELOCITY(500.0f);

class Game {
public:
    GameState mState;
    GLboolean mKeys[1024];
    GLuint mWidth, mHeight;
    std::vector<GameLevel> Levels;
    GLuint Level;
    
    // Constructor / Destructor
    Game(GLuint width, GLuint height);
    ~Game();
    
    void Initialize();
    // Game Loop
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();
	float floatModulo(float top, float bottom);
	std::string getAnimationTexture(float positionX);
    
    static Game* GetInstance() { return instance; };

private:
    static Game* instance;
};

#endif /* Game_h */
