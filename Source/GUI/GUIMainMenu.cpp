//
//  GUIGameMenu.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-06.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "GUIMainMenu.h"

#include "GUIButton.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "EventManager.h"
#include "TextRenderer.h"
#include "AudioEngine.h"
#include "Game.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

using namespace std;

GUIMainMenu::GUIMainMenu() { }

bool GUIMainMenu::Initialize() {
    currentSelection = 0;
    // start game
    std::shared_ptr<GUIButton> startGame(new GUIButton); // selection 0
    startGame->SetName("startGame");
    startGame->SetPosition(glm::vec2(410.0f, EventManager::GetScreenHeight() / 2 - 300.0f));
    startGame->SetScale(glm::vec2(mScale.x * 0.4f, 50.0f));
    startGame->SetForeColor(glm::vec4(glm::vec3(0.6f), 1.0f));
    startGame->SetHoverColor(glm::vec4(1.0f));
    startGame->SetText("Start Game");
    // continue (?) will need to cache if we do
    std::shared_ptr<GUIButton> continueGame(new GUIButton); // selection 1
    continueGame->SetName("continueGame");
    continueGame->SetPosition(glm::vec2(410.0f, EventManager::GetScreenHeight() / 2 - 250.0f));
    continueGame->SetScale(glm::vec2(mScale.x * 0.4f, 50.0f));
    continueGame->SetForeColor(glm::vec4(glm::vec3(0.6f), 1.0f));
    continueGame->SetHoverColor(glm::vec4(1.0f));
    continueGame->SetText("Continue");
    // start game
    std::shared_ptr<GUIButton> quitGame(new GUIButton); // selection 2
    quitGame->SetName("quitGame");
    quitGame->SetPosition(glm::vec2(410.0f, EventManager::GetScreenHeight() / 2 - 200.0f));
    quitGame->SetScale(glm::vec2(mScale.x * 0.4f, 50.0f));
    quitGame->SetForeColor(glm::vec4(glm::vec3(0.6f), 1.0f));
    quitGame->SetHoverColor(glm::vec4(1.0f));
    quitGame->SetText("Quit Game");
    
    AddElement(startGame);
    AddElement(continueGame);
    AddElement(quitGame);
    
    mBackgroundTexture = &ResourceManager::GetTexture("background");
    return true;
}

void GUIMainMenu::Update(float dt) {
    
    
}

void GUIMainMenu::RenderBackground(Renderer *renderer, TextRenderer *text) {
    renderer->Render(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(EventManager::GetScreenWidth(), EventManager::GetScreenHeight()), 0.0f);
    text->RenderText("GOLDEN SPHERE", 410.0f, EventManager::GetScreenHeight() / 2 - 350.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
}

void GUIMainMenu::Activate() {
    Game::GetInstance()->GetAudio()->StopAll();
    Game::GetInstance()->GetAudio()->PlaySound("Sounds/caketown.wav", true);
}

void GUIMainMenu::Deactivate() {
    Game::GetInstance()->GetAudio()->StopSound("Sounds/caketown.wav");
}

void GUIMainMenu::select(){
    switch(currentSelection){
        
        case 0: ; // start game
        case 1: ; // continue game
        case 2: ; // exit game
    }
};


void GUIMainMenu::changeMenuState(){
    if(GLFW_KEY_W | GLFW_KEY_UP){
        selectionUp();
    };
    if(GLFW_KEY_S | GLFW_KEY_DOWN){
        selectionDown();
    };
    if(GLFW_KEY_ENTER){
        select();
    };
};

void GUIMainMenu::selectionUp(){
    currentSelection--;
    
    if(currentSelection == -1){
        currentSelection = 2;
    };
};

void GUIMainMenu::selectionDown(){
    currentSelection++;
    
    if(currentSelection == 3){
        currentSelection = 0;
    };
};
