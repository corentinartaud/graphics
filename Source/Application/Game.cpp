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
#include "TextRenderer.h"
#include "GUIMainMenu.h"
#include <string>
#include <iostream>

using namespace std;

Game* Game::instance;

Renderer *renderer;
GameObject *player;

TextRenderer *text;

Game::Game(GLuint width, GLuint height)
: mState(GAME_ACTIVE), mKeys(), mWidth(width), mHeight(height) {
    instance = this;
}

Game::~Game() {
    delete renderer;
    delete player;
    delete text;
}

void Game::Initialize() {
    // Load shaders
#if defined(PLATFORM_OSX)	
	ResourceManager::LoadShader("Shaders/texture.vertexshader", "Shaders/texture.fragmentshader", "texture");
#else
	ResourceManager::LoadShader("../Assets/Shaders/texture.vertexshader", "../Assets/Shaders/texture.fragmentshader", "texture");
#endif
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->mWidth), 0.0f, static_cast<GLfloat>(this->mHeight), -1.0f, 1.0f);
    ResourceManager::GetShader("texture").Use().SetInteger("image", 0);
    ResourceManager::GetShader("texture").SetMatrix4("projection", projection);
    // Load textures
#if defined(PLATFORM_OSX)	
	ResourceManager::LoadTexture("Textures/background.jpg", GL_TRUE, "background");
	ResourceManager::LoadTexture("Textures/Player/stand/s1.png", GL_TRUE, "player");
	ResourceManager::LoadTexture("Textures/Platform/Grass.png", GL_TRUE, "grass");
	ResourceManager::LoadTexture("Textures/Platform/Ground.png", GL_TRUE, "ground");
#else
	ResourceManager::LoadTexture("../Assets/Textures/background.jpg", GL_TRUE, "background");
	ResourceManager::LoadTexture("../Assets/Textures/Player/stand/s1.png", GL_TRUE, "player");
	ResourceManager::LoadTexture("../Assets/Textures/Platform/Grass.png", GL_TRUE, "grass");
	ResourceManager::LoadTexture("../Assets/Textures/Platform/Ground.png", GL_TRUE, "ground");
#endif
    // Set render-specific controls
    renderer = new Renderer(ResourceManager::GetShader("texture"));
    // Set text
    text = new TextRenderer(EventManager::GetScreenWidth(), EventManager::GetScreenHeight());
#if defined(PLATFORM_OSX)
    text->Load("Fonts/OCRAEXT.TTF", 24);
#else
    text->Load("../Assets/Fonts/OCRAEXT.TTF", 24);
#endif
    // Load levels
    GameLevel one;
#if defined(PLATFORM_OSX)
    player = one.Load("levels/one.lvl", this->mWidth, this->mHeight * 0.5);
#else
	player = one.Load("../Assets/levels/one.lvl", this->mWidth, this->mHeight * 0.5);
#endif
    this->Levels.push_back(one);
    this->Level = 0;
    
    mGUIContainers["main_menu"] = std::shared_ptr<GUIContainer>(new GUIMainMenu);
    for(auto it = mGUIContainers.begin(); it != mGUIContainers.end(); ++it)
        it->second->Initialize();
}

void Game::Update(float dt) { }

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
        //jumping 
        if ((this->mKeys[GLFW_KEY_SPACE] || this->mKeys[GLFW_KEY_UP])) {

            if(player->mPosition.y < 300){
                player->mVelocity.y = 675.0f;
                player->mPosition.y += player->mVelocity.y * dt;
                std::cout << "UP: " << player->mPosition.y << std::endl;
            }
        }
        else {
            if(player->mPosition.y > 100.0){
                player->mPosition.y -= player->mVelocity.y * dt;
            }
        }
    }
}

void Game::Render() {
    EventManager::BeginFrame();
    if (this->mState == GAME_ACTIVE) {
        // Draw background
        renderer->Render(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(this->mWidth, this->mHeight), 0.0f);
        // Draw level
        this->Levels[this->Level].Draw(*renderer);
        // Draw player
		ResourceManager::LoadTexture(getAnimationTexture(player->mPosition.x).c_str(), GL_TRUE, "player");	//update texture
		player->mTexture = ResourceManager::GetTexture("player");	//update player with new texture
        player->Draw(*renderer);
    }
    else if (this->mState == GAME_MENU) {
        //text->RenderText("Press ENTER to start", 250.0f, EventManager::GetScreenWidth() / 2, 1.0f);
        //text->RenderText("Press W or S to select level", 245.0f, EventManager::GetScreenHeight() / 2 + 20.0f, 0.75f);
        for (auto it = mGUIContainers.begin(); it != mGUIContainers.end(); ++it) {
            it->second->RenderBackground(renderer, text);
        }
    }
    EventManager::EndFrame();
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
	frameNumber = min(frameNumber, 5);	//clamp upper
	frameNumber = max(frameNumber, 0);	//clamp lower
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
