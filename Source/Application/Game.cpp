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
#include "GUILost.h"
#include "AudioEngine.h"
#include "TextRenderer.h"
#include <string>
#include <iostream>
#include <list>
using namespace std;

Game* Game::instance;

Game::Game() {
    instance = this;
    
    mAudio = new AudioEngine();
    mText = new TextRenderer();
    
    this->Initialize(EventManager::GetScreenWidth(), EventManager::GetScreenHeight());
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

Game::~Game() {
    delete engine;
    delete mAudio;
}

void Game::Initialize(GLuint width, GLuint height) {
    mWidth = width;
    mHeight = height;
    
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
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->mWidth), 0.0f, static_cast<GLfloat>(this->mHeight), -1.0f, 1.0f);
    ResourceManager::GetShader("texture").Use().SetInteger("image", 0);
    ResourceManager::GetShader("texture").SetMatrix4("projection", projection);
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
	ResourceManager::LoadTexture("Textures/background.jpg", GL_TRUE, "background");
	ResourceManager::LoadTexture("Textures/Player/stand/s1.png", GL_TRUE, "player");
	ResourceManager::LoadTexture("Textures/Platform/Grass.png", GL_TRUE, "grass");
	ResourceManager::LoadTexture("Textures/Platform/Ground.png", GL_TRUE, "ground");
    ResourceManager::LoadTexture("Textures/Spikes/setB/spike.png", GL_TRUE, "spike");
#else
	ResourceManager::LoadTexture("../Assets/Textures/background.jpg", GL_TRUE, "background");
	ResourceManager::LoadTexture("../Assets/Textures/Player/stand/s1.png", GL_TRUE, "player");
	ResourceManager::LoadTexture("../Assets/Textures/Spikes/setB/spike.png", GL_TRUE, "grass");
	ResourceManager::LoadTexture("../Assets/Textures/Platform/Ground.png", GL_TRUE, "ground");
    ResourceManager::LoadTexture("../Assets/Textures/Spikes/setB/spike.png", GL_TRUE, "spike");
#endif
    // Set render-specific controls
    renderer = new Renderer(ResourceManager::GetShader("texture"));
    // Load levels
    //GameLevel one;
#if defined(PLATFORM_OSX)
    player = one.Load("levels/one.lvl", this->mWidth, this->mHeight * 0.5);
#else
	player = one.Load("../Assets/levels/one.lvl", this->mWidth, this->mHeight * 0.5);
#endif
    this->Levels.push_back(one);
    this->Level = 0;
    
    engine = new GameEngine(player, one.Platforms, one.Spikes, GRAVITY, PLAYER_VELOCITY);
    animations = new Animation();
    
    mGUIContainers["MainMenu"] = std::shared_ptr<GUIContainer>(new GUIMainMenu);
    mGUIContainers["PauseMenu"] = std::shared_ptr<GUIPauseMenu>(new GUIPauseMenu);
    mGUIContainers["LostMenu"] = std::shared_ptr<GUILost>(new GUILost);
    
    for(auto it = mGUIContainers.begin(); it != mGUIContainers.end(); ++it)
        it->second->Initialize();
    
    SwitchStates(GameState::GAME_MAIN_MENU);
}

void Game::ReloadGame() {
#if defined(PLATFORM_OSX)
    player = one.Load("levels/one.lvl", this->mWidth, this->mHeight * 0.5);
#else
    player = one.Load("../Assets/levels/one.lvl", this->mWidth, this->mHeight * 0.5);
#endif
    if (Levels.size() > 0)
        Levels.clear();
    this->Levels.push_back(one);
    this->Level = 0;
    
    engine = new GameEngine(player, one.Platforms, one.Spikes, GRAVITY, PLAYER_VELOCITY);
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
            if (engine == nullptr && player == nullptr)
                ReloadGame();
            GetAudio()->StopAll();
            GetAudio()->PlaySound("Sounds/awesomeness.wav", true);
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
        case GameState::GAME_LOSE:
            mGUIContainers["LostMenu"]->SetActive(true);
        default:
            break;
    }
}

void Game::Update(float dt) {
    if (mState == GAME_ACTIVE) {
        engine->Update(dt);
        if (engine->HitSpikes()) {
            SwitchStates(GAME_LOSE);
            engine = nullptr; player = nullptr;
        }
        
    }
}

// process input for every frame during game state
void Game::ProcessInput(GLfloat dt) {

    if (this->mState == GAME_ACTIVE) {
        GLfloat velocity = PLAYER_VELOCITY * dt;
        // Move player
        if (this->mKeys[GLFW_KEY_A] || this->mKeys[GLFW_KEY_LEFT]) {
            if (player->mPosition.x >= 0)
                player->mPosition.x -= velocity;
        }
        if (this->mKeys[GLFW_KEY_D] || this->mKeys[GLFW_KEY_RIGHT] ) {
            if (player->mPosition.x <= this->mWidth - player->mSize.x)
                player->mPosition.x += velocity;
        }
        // Jumping
        // Only allow to jump when player is on a platform
        if ((this->mKeys[GLFW_KEY_SPACE] || this->mKeys[GLFW_KEY_UP]) && player->mVelocity.y == 0.f) {
            player->mVelocity.y = JUMP_VELOCITY;
			animations->addSmoke(*player, Jump);
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
        renderer->Render(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(this->mWidth, this->mHeight), 360.0f);
        // Get the view matrix
        glm::mat4 viewMatrix = glm::translate(glm::mat4(1.f), glm::vec3(player->mInitialPosition.x - player->mPosition.x, 0.f, 0.f));
        // Draw level
        this->Levels[this->Level].Draw(*renderer, viewMatrix);
        // Set Player Animation
		animations->setPlayerAnimation(*player);
		player->mTexture = ResourceManager::GetTexture("player");	//update player with new texture
		//Draw Phantoms
		animations->DrawPhantom(*renderer, viewMatrix);
		animations->DrawSmoke(*renderer, viewMatrix);
		//Draw Player
		player->Draw(*renderer, viewMatrix);
    }
    std::cout << (mState == GAME_LOSE) << std::endl;
    for (auto it = mGUIContainers.begin(); it != mGUIContainers.end(); ++it)
        it->second->Render(renderer, mText);
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
