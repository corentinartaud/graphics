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

Game* Game::instance;

Renderer *renderer;
GameObject *player;

Game::Game(GLuint width, GLuint height)
: mState(GAME_ACTIVE), mKeys(), mWidth(width), mHeight(height) {
    instance = this;
}

Game::~Game() {
    
}

void Game::Initialize() {
    // Load shaders
    ResourceManager::LoadShader("Shaders/texture.vertexshader", "Shaders/texture.fragmentshader", nullptr, "texture");
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->mWidth), static_cast<GLfloat>(this->mHeight), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("texture").Use().SetInteger("image", 0);
    ResourceManager::GetShader("texture").SetMatrix4("projection", projection);
    // Load textures
    ResourceManager::LoadTexture("Textures/background.jpg", GL_TRUE, "background");
    ResourceManager::LoadTexture("Textures/Player/stand/s1.png", GL_TRUE, "player");
    ResourceManager::LoadTexture("Textures/Platform/Grass.png", GL_TRUE, "grass");
    // Set render-specific controls
    renderer = new Renderer(ResourceManager::GetShader("texture"));
    // Load levels
    GameLevel one; one.Load("levels/one.lvl", this->mWidth, this->mHeight * 0.5);
    this->Levels.push_back(one);
    this->Level = 0;
    // Configure game objects
    glm::vec2 playerPos = glm::vec2(this->mWidth / 2 - PLAYER_SIZE.x / 2, this->mHeight - PLAYER_SIZE.y - 50);
    player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("player"));
}

void Game::Update(float dt) { }

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
        if (this->mKeys[GLFW_KEY_SPACE] || this->mKeys[GLFW_KEY_UP]) {
            // @TODO MUST IMPLEMENT GRAVITY AND ALL THAT SHIT 
            if (player->mPosition.y <= this->mHeight / 2)
                player->mPosition.y += velocity;
            else
                player->mPosition.y -= velocity;
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
        player->Draw(*renderer);
    }
    EventManager::EndFrame();
}
