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
    delete mPlayer;
    delete mRenderer;
    delete mText;
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
	ResourceManager::LoadTexture("../Assets/Textures/Platform/Grass.png", GL_TRUE, "grass");
	ResourceManager::LoadTexture("../Assets/Textures/Platform/Ground.png", GL_TRUE, "ground");
    ResourceManager::LoadTexture("../Assets/Textures/Spikes/setB/spike.png", GL_TRUE, "spike");
#endif
    // Set render-specific controls
    mRenderer->Initialize(ResourceManager::GetShader("texture"));
    // Load levels
    //GameLevel one;
#if defined(PLATFORM_OSX)
    mPlayer = one.Load("levels/two.lvl", this->mWidth, this->mHeight * 0.5);
#else
	player = one.Load("../Assets/levels/one.lvl", this->mWidth, this->mHeight * 0.5);
#endif
    this->Levels.push_back(one);
    this->Level = 0;
    
    mEngine = new GameEngine(mPlayer, one.Platforms, one.Spikes, GRAVITY, PLAYER_VELOCITY);
    
    mGUIContainers["MainMenu"] = std::shared_ptr<GUIContainer>(new GUIMainMenu);
    mGUIContainers["PauseMenu"] = std::shared_ptr<GUIPauseMenu>(new GUIPauseMenu);
    mGUIContainers["LostMenu"] = std::shared_ptr<GUILost>(new GUILost);
    
    for(auto it = mGUIContainers.begin(); it != mGUIContainers.end(); ++it)
        it->second->Initialize();
    
    SwitchStates(GameState::GAME_MAIN_MENU);
}

void Game::ReloadGame() {
    delete mPlayer; delete mEngine;
    mPlayer = new GameObject();
#if defined(PLATFORM_OSX)
    mPlayer = one.Load("levels/two.lvl", this->mWidth, this->mHeight * 0.5);
#else
    player = one.Load("../Assets/levels/one.lvl", this->mWidth, this->mHeight * 0.5);
#endif
    if (Levels.size() > 0)
        Levels.clear();
    this->Levels.push_back(one);
    this->Level = 0;
    
    mEngine = new GameEngine(mPlayer, one.Platforms, one.Spikes, GRAVITY, PLAYER_VELOCITY);
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
            if (mEngine == nullptr && mPlayer == nullptr)
                ReloadGame();
            GetAudio()->StopAll();
            GetAudio()->Play("Sounds/awesomeness.wav", true);
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
        mEngine->Update(dt);
        if (mEngine->HitSpikes()) {
            SwitchStates(GAME_LOSE);
            mEngine = nullptr; mPlayer = nullptr;
        }
        
    }
}

// process input for every frame during game state
void Game::ProcessInput(GLfloat dt) {

    if (this->mState == GAME_ACTIVE) {
        GLfloat velocity = PLAYER_VELOCITY * dt;
        // Move player
        if (this->mKeys[GLFW_KEY_A] || this->mKeys[GLFW_KEY_LEFT]) {
            if (mPlayer->mPosition.x >= 0)
                mPlayer->mPosition.x -= velocity;
        }
        if (this->mKeys[GLFW_KEY_D] || this->mKeys[GLFW_KEY_RIGHT] ) {
            if (mPlayer->mPosition.x <= this->mWidth - mPlayer->mSize.x)
                mPlayer->mPosition.x += velocity;
        }
        // Jumping
        // Only allow to jump when player is on a platform
        if ((this->mKeys[GLFW_KEY_SPACE] || this->mKeys[GLFW_KEY_UP]) && mPlayer->mVelocity.y == 0.f) {
            mPlayer->mVelocity.y = JUMP_VELOCITY;
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
        glm::mat4 viewMatrix = glm::translate(glm::mat4(1.f), glm::vec3(mPlayer->mInitialPosition.x - mPlayer->mPosition.x, 0.f, 0.f));
        // Draw level
        this->Levels[this->Level].Draw(*mRenderer, viewMatrix);
        // Draw player
		ResourceManager::LoadTexture(getAnimationTexture(mPlayer->mPosition.x).c_str(), GL_TRUE, "player");	//update texture
		mPlayer->mTexture = ResourceManager::GetTexture("player");	//update player with new texture
        mPlayer->Draw(*mRenderer, viewMatrix);
    }
    std::cout << (mState == GAME_LOSE) << std::endl;
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

float Game::floatModulo(float top, float bottom)
{
	uint8_t division = top / bottom;
	return top - (bottom * (float)division);
}

std::string Game::getAnimationTexture(float positionX) {
	const std::string standRight[6] = {
		"Textures/Player/stand/s1.png",
		"Textures/Player/stand/s2.png",
		"Textures/Player/stand/s3.png",
		"Textures/Player/stand/s4.png",
		"Textures/Player/stand/s5.png",
		"Textures/Player/stand/s6.png"
	};
	const std::string walkRight[6] = {
		"Textures/Player/walk/w1.png",
		"Textures/Player/walk/w2.png",
		"Textures/Player/walk/w3.png",
		"Textures/Player/walk/w4.png",
		"Textures/Player/walk/w5.png",
		"Textures/Player/walk/w6.png"
	};
	const std::string standLeft[6] = {
		"Textures/Player/stand/Mirrored/s1.png",
		"Textures/Player/stand/Mirrored/s2.png",
		"Textures/Player/stand/Mirrored/s3.png",
		"Textures/Player/stand/Mirrored/s4.png",
		"Textures/Player/stand/Mirrored/s5.png",
		"Textures/Player/stand/Mirrored/s6.png"
	};
	const std::string walkLeft[6] = {
		"Textures/Player/walk/Mirrored/w1.png",
		"Textures/Player/walk/Mirrored/w2.png",
		"Textures/Player/walk/Mirrored/w3.png",
		"Textures/Player/walk/Mirrored/w4.png",
		"Textures/Player/walk/Mirrored/w5.png",
		"Textures/Player/walk/Mirrored/w6.png"
	};
#define still 0
#define forward 1
#define backward 2
	static uint8_t pastDirection = 0;	//stores past direction of movement, everytime the movement direction changes, restart the animation timer
	static float pastPositionX = 0;	//stores past position, knowign past position and new position give direction, basically velocity beign positive or negative
	static bool mirroredStatus = false;	//stores whether player texture should be mirrored
	uint8_t direction = 0;	//direction of movement
		//checking current movement direction
	if (positionX > pastPositionX) {
		direction = forward;
		mirroredStatus = false;
	}
	else if (positionX < pastPositionX) {
		direction = backward;
		mirroredStatus = true;
	}
	else {
		direction = still;
	}
	pastPositionX = positionX;
	//calculating time since animation began
	static float timeElapsed = 0;
	if (pastDirection != direction) {
		timeElapsed = 0;
	}
	else {
		timeElapsed += EventManager::GetFrameTime();
	}
	pastDirection = direction;
	//calculate which animation frame to be in
#define totalCycleTime 0.5f //in seconds
	float cycleTime = floatModulo(timeElapsed, totalCycleTime);
	int frameNumber = cycleTime / (totalCycleTime / 6);	//calculate frame number from 0-5
    frameNumber = std::min(frameNumber, 5);	//clamp upper
    frameNumber = std::max(frameNumber, 0);	//clamp lower
	std::string framePath;
	if (mirroredStatus == true) {
		if (direction == 0) {
			framePath = standLeft[frameNumber];
		}
		else framePath = walkLeft[frameNumber];
	}
	else {
		if (direction == 0) {
			framePath = standRight[frameNumber];
		}
		else framePath = walkRight[frameNumber];
	}
#if defined(PLATFORM_OSX)	
	return framePath;
#else 
	return "../Assets/" + framePath;
#endif
}
