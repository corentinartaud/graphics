//
//  Game.h
//  COMP371_Project
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#ifndef Game_h
#define Game_h

<<<<<<< HEAD
#include <array>
=======
#include "GameState.h"
#include "GameLevel.h"
#include "GameEngine.h"
>>>>>>> bf8cac53ce5ecb9bd4526344924f697b542a919c

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GameLevel.h"
#include "GameEngine.h"

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100, 100);
// Initial velocity of the player paddle
const GLfloat PLAYER_VELOCITY(150.0f);
// Gravity acceleration towards the ground
const GLfloat GRAVITY(-400.f);
// Player initial jump velocity
const GLfloat JUMP_VELOCITY(300.f);

class Game {
public:
    GameState mState;
    GLboolean mKeys[1024];
    GLuint mWidth, mHeight;
    std::vector<GameLevel> Levels;
    GLuint Level;
    GameEngine* engine;
    
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
<<<<<<< HEAD
    static Game* instance;
=======
    
    AudioEngine *mAudio;
    Renderer *mRenderer;
    GameObject *mPlayer;
    TextRenderer *mText;
    GameEngine *mEngine;
    
    std::map<std::string, std::shared_ptr<GUIContainer>> mGUIContainers; // contains all the game's GUI items
    static Game *mInstance;
>>>>>>> bf8cac53ce5ecb9bd4526344924f697b542a919c
};

#endif /* Game_h */
