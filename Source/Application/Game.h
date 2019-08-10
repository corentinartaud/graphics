//
//  Game.h
//  COMP371_Project
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include "GameState.h"
#include "GameLevel.h"
#include "GameEngine.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <array>
#include <map>
#include <memory>

class GUIContainer;
class AudioEngine;
class TextRenderer;

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
    bool mKeys[1024];
    float mWidth, mHeight;
    std::vector<GameLevel> Levels;
    GLuint Level;
    
    // Constructor / Destructor
    Game();
    ~Game();
    
    void GameLoop();
    
    void Initialize(float width, float height);
    // Game Loop
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();
	float floatModulo(float top, float bottom);
	std::string getAnimationTexture(float positionX);
    
    static Game* GetInstance() { return mInstance; };
    
    // returns the game's audio sub-system
    AudioEngine* const GetAudio() { return mAudio; };
    
    // process mouse mouvement in OS-independent manner
    void ProcessMouseMove(float x, float y);
    // processes mouse button clicks in OS-independent manner
    void ProcessMouseClick(bool leftButton);
    
    // switches the game states
    void SwitchStates(GameState state = GameState::GAME_NULL);

private:
    
    AudioEngine *mAudio;
    Renderer *mRenderer;
    GameObject *mPlayer;
    TextRenderer *mText;
    GameEngine *mEngine;
    
    std::map<std::string, std::shared_ptr<GUIContainer>> mGUIContainers; // contains all the game's GUI items
    static Game *mInstance;
};

#endif /* Game_h */
