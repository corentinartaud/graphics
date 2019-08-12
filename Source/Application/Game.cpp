//
//  Game.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "Game.h"
#include "EventManager.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "GUIContainer.h"
#include "GUIMainMenu.h"
#include "GUIPauseMenu.h"
#include "GUILevelMenu.h"
#include "GUILost.h"
#include "AudioEngine.h"
#include "TextRenderer.h"
#include <string>
#include <iostream>
#include <list>

Game* Game::instance;

Game::Game() {
    instance = this;
    
    mAudio = new AudioEngine();
    mText = new TextRenderer();
    mRenderer = new Renderer();
    
    this->Initialize(EventManager::GetScreenWidth(), EventManager::GetScreenHeight());
}

Game::~Game() {
    delete mEngine;
    delete mAudio;
    delete mRenderer;
    delete mText;
    for (auto it : mPlayer)
        delete it;
}

void Game::GameLoop() {
    do {
        EventManager::Update();
        float dt = EventManager::GetFrameTime();
        this->ProcessInput(dt);
        this->Update(dt);
        this->Render();
    } while(!EventManager::ExitRequested());
}

void Game::Initialize(float width, float height) {
    // set width and height of the game
    mWidth = width;
    mHeight = height;
    
    // load all audio
    mAudio->Load();
    
    // Load shaders
#if defined(PLATFORM_OSX)
    ResourceManager::LoadShader("Shaders/texture.vertexshader", "Shaders/texture.fragmentshader", "texture");
    ResourceManager::LoadShader("Shaders/text.vertexshader", "Shaders/text.fragmentshader", "text");
    ResourceManager::LoadShader("Shaders/gui.vertexshader", "Shaders/gui.fragmentshader", "gui");
#else
    ResourceManager::LoadShader("../Assets/Shaders/texture.vertexshader", "../Assets/Shaders/texture.fragmentshader", "texture");
    ResourceManager::LoadShader("../Assets/Shaders/text.vertexshader", "../Assets/Shaders/text.fragmentshader", "text");
    ResourceManager::LoadShader("../Assets/Shaders/gui.vertexshader", "../Assets/Shaders/gui.fragmentshader", "gui");
#endif
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
    ResourceManager::GetShader("texture").Use().SetInteger("image", 0);
    ResourceManager::GetShader("texture").SetMatrix4("projection", projection);
    // Set render-specific controls
    mRenderer->Initialize(ResourceManager::GetShader("texture"));
    // Set text-specific control
    mText->Initialize(EventManager::GetScreenWidth(), EventManager::GetScreenHeight());
    // Load Fonts
#if defined(PLATFORM_OSX)
    mText->LoadFont("Fonts/CUTIVEMONO-REGULAR.TTF", 50);
#else
    mText->LoadFont("../Assets/Fonts/CUTIVEMONO-REGULAR.TTF", 50);
#endif
    // Load textures
#if defined(PLATFORM_OSX)	
	ResourceManager::LoadTexture("Textures/background.jpg", "background");
	ResourceManager::LoadTexture("Textures/Player/stand/s1.png", "player");
	ResourceManager::LoadTexture("Textures/Platform/GrassNGrass.png", "grass");
	ResourceManager::LoadTexture("Textures/Platform/Ground.png", "ground");
    ResourceManager::LoadTexture("Textures/Spikes/setB/spike.png", "spike");
#else
	ResourceManager::LoadTexture("../Assets/Textures/background.jpg", "background");
	ResourceManager::LoadTexture("../Assets/Textures/Player/stand/s1.png", "player");
	ResourceManager::LoadTexture("../Assets/Textures/Platform/Grass.png", "grass");
	ResourceManager::LoadTexture("../Assets/Textures/Platform/Ground.png", "ground");
    ResourceManager::LoadTexture("../Assets/Textures/Spikes/setB/spike.png", "spike");
#endif
    
    mGUIContainers["MainMenu"] = std::shared_ptr<GUIContainer>(new GUIMainMenu);
    mGUIContainers["PauseMenu"] = std::shared_ptr<GUIPauseMenu>(new GUIPauseMenu);
    mGUIContainers["LevelMenu"] = std::shared_ptr<GUILevelMenu>(new GUILevelMenu);
    mGUIContainers["LostMenu"] = std::shared_ptr<GUILost>(new GUILost);
    
    for(auto it = mGUIContainers.begin(); it != mGUIContainers.end(); ++it)
        it->second->Initialize();
    
    SwitchStates(GameState::GAME_MAIN_MENU);
}

void Game::LoadGame() {
    if (mEngine == nullptr && mPlayer.empty()) {
        for (auto it : mPlayer)
            delete it;
        delete mEngine;
    }
    // clear all level data
    if (Levels.size() > 0)
        Levels.clear();

    // Load levels
#if defined(PLATFORM_OSX)
    mPlayer.push_back(gameLevel.Load("levels/one.lvl", this->mWidth, this->mHeight * 0.5));
    this->Levels.push_back(gameLevel);
    mPlayer.push_back(gameLevel.Load("levels/two.lvl", this->mWidth, this->mHeight * 0.5));
    this->Levels.push_back(gameLevel);
    mPlayer.push_back(gameLevel.Load("levels/three.lvl", this->mWidth, this->mHeight * 0.5));
    this->Levels.push_back(gameLevel);
#else
    mPlayer = gameLevel.Load("../Assets/levels/one.lvl", this->mWidth, this->mHeight * 0.5);
    this->Levels.push_back(gameLevel);
    mPlayer = gameLevel.Load("../Assets/levels/two.lvl", this->mWidth, this->mHeight * 0.5);
    this->Levels.push_back(gameLevel);
    mPlayer = gameLevel.Load("../Assets/levels/three.lvl", this->mWidth, this->mHeight * 0.5);
    this->Levels.push_back(gameLevel);
#endif
    
    // create new game engine
    mEngine = new GameEngine(mPlayer[this->Level], this->Levels[this->Level].Platforms, this->Levels[this->Level].Spikes, GRAVITY, PLAYER_VELOCITY);
    // reset animations
    mAnimations = new Animation();
}

void Game::SwitchStates(GameState state) {
    mState = (state == GameState::GAME_NULL ? mState : state);
    // de-activate all GUI containers in order to avoid irrelevant sounds
    for (auto it = mGUIContainers.begin(); it != mGUIContainers.end(); ++it)
        it->second->SetActive(false);

    switch(state) {
        case GameState::GAME_MAIN_MENU:
            mGUIContainers["MainMenu"]->SetActive(true);
            break;
        case GameState::GAME_ACTIVE:
            GetAudio()->StopAll();
            GetAudio()->Play("Sounds/awesomeness.wav", true);
            LoadGame();
            break;
        case GameState::GAME_WIN:
            break;
        case GameState::GAME_NULL:
            EventManager::SetWindowShouldClose();
            break;
        case GameState::GAME_INGAME_MENU:
            GetAudio()->StopAll();
            mGUIContainers["PauseMenu"]->SetActive(true);
            break;
        case GameState::GAME_LEVEL:
            mGUIContainers["LevelMenu"]->SetActive(true);
            break;
        case GameState::GAME_LEVEL_1:
            GetAudio()->StopAll();
            this->Level = 0;
            SwitchStates(GAME_ACTIVE);
            break;
        case GameState::GAME_LEVEL_2:
            GetAudio()->StopAll();
            this->Level = 1;
            SwitchStates(GAME_ACTIVE);
            break;
        case GameState::GAME_LEVEL_3:
            GetAudio()->StopAll();
            this->Level = 2;
            SwitchStates(GAME_ACTIVE);
            break;
        case GameState::GAME_LOSE:
            mEngine = nullptr;
            mPlayer.clear();
            mGUIContainers["LostMenu"]->SetActive(true);
        default:
            break;
    }
}

void Game::Update(float dt) {
    if (mState == GAME_ACTIVE) {
        mEngine->Update(dt);
        if (mEngine->HitSpikes()) {
            SwitchStates(GAME_LOSE);
        }
    }
}

// process input for every frame during game state
void Game::ProcessInput(GLfloat dt) {
    if (this->mState == GAME_ACTIVE) {
        // Jumping
        if ((this->mKeys[GLFW_KEY_SPACE] || this->mKeys[GLFW_KEY_UP] || this->mKeys[GLFW_KEY_W] || this->mKeys[GLFW_MOUSE_BUTTON_LEFT]) && mPlayer[this->Level]->mVelocity.y == 0.f) {
            mPlayer[this->Level]->mVelocity.y = JUMP_VELOCITY;
			mAnimations->addSmoke(*mPlayer[this->Level], Jump);
        }
        // check for pause
        if (this->mKeys[GLFW_KEY_P]){
            Game::GetInstance()->SwitchStates(GAME_INGAME_MENU);
        }
    }
}

void Game::Render() {
    EventManager::BeginFrame();
    if (this->mState == GAME_ACTIVE) {
        // Draw background
        mRenderer->Render(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(this->mWidth, this->mHeight), 360.0f);
        // Get the view matrix
        glm::mat4 viewMatrix = glm::translate(glm::mat4(1.f), glm::vec3(mPlayer[this->Level]->mInitialPosition.x - mPlayer[this->Level]->mPosition.x, 0.f, 0.f));
        // Draw level
        this->Levels[this->Level].Draw(*mRenderer, viewMatrix);
        // Set Player Animation
        mAnimations->setPlayerAnimation(*mPlayer[this->Level]);
		mPlayer[this->Level]->mTexture = ResourceManager::GetTexture("player");	//update player with new texture
		//Draw Phantoms
        mAnimations->DrawPhantom(*mRenderer, viewMatrix);
        mAnimations->DrawSmoke(*mRenderer, viewMatrix);
		//Draw Player
		mPlayer[this->Level]->Draw(*mRenderer, viewMatrix);
    }
    for (auto it = mGUIContainers.begin(); it != mGUIContainers.end(); ++it)
        it->second->Render(mRenderer, mText);
    EventManager::EndFrame();
}

void Game::ProcessMouseMove(float x, float y) {
    for (auto it = mGUIContainers.begin(); it != mGUIContainers.end(); ++it)
        it->second->OnMouseMove(x, y);
}

void Game::ProcessMouseClick(bool leftButton) {
    for (auto it = mGUIContainers.begin(); it != mGUIContainers.end(); ++it)
        it->second->OnMouseClick(leftButton);
}
