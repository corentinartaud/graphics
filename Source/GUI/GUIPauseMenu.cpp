//
//  GUIPauseMenu.cpp
//  COMP371_Framework
//
//  Created by Steven Anthony on 2019-08-10.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "GUIPauseMenu.h"
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

GUIPauseMenu::GUIPauseMenu() { }

bool GUIPauseMenu::Initialize() {
<<<<<<< HEAD
=======
    // set scale
    SetScale(glm::vec2(EventManager::GetScreenWidth(), EventManager::GetScreenHeight()));
>>>>>>> bf8cac53ce5ecb9bd4526344924f697b542a919c
    
    // Resume Game
    std::shared_ptr<GUIButton> resumeGame(new GUIButton);
    resumeGame->SetName("resumeGame");
<<<<<<< HEAD
    resumeGame->SetPosition(glm::vec2(380.0f, EventManager::GetScreenHeight() / 2 - 100));
    resumeGame->SetScale(glm::vec2(mScale.x * 0.4f, 50.0f));
=======
    resumeGame->SetPosition(glm::vec2(mScale.x * 0.35f, mScale.y / 2 - 100.0f));
    resumeGame->SetScale(glm::vec2(mScale.x * 0.4f, 20.0f));
>>>>>>> bf8cac53ce5ecb9bd4526344924f697b542a919c
    resumeGame->SetForeColor(glm::vec3(1.0f));
    resumeGame->SetHoverColor(glm::vec4(0.0f));
    resumeGame->SetText("Resume Game");
    
    // Save Game
    std::shared_ptr<GUIButton> saveGame(new GUIButton);
    saveGame->SetName("saveGame");
<<<<<<< HEAD
    saveGame->SetPosition(glm::vec2(380.0f, EventManager::GetScreenHeight() / 2));
    saveGame->SetScale(glm::vec2(mScale.x * 0.4f, 50.0f));
=======
    saveGame->SetPosition(glm::vec2(mScale.x * 0.35f, mScale.y / 2));
    saveGame->SetScale(glm::vec2(mScale.x * 0.4f, 20.0f));
>>>>>>> bf8cac53ce5ecb9bd4526344924f697b542a919c
    saveGame->SetForeColor(glm::vec3(1.0f));
    saveGame->SetHoverColor(glm::vec4(0.0f));
    saveGame->SetText("Save Game");
    
    
    // Quit Game
    std::shared_ptr<GUIButton> quitGame(new GUIButton);
    quitGame->SetName("quitGame");
<<<<<<< HEAD
    quitGame->SetPosition(glm::vec2(380.0f, EventManager::GetScreenHeight() / 2 + 100));
    quitGame->SetScale(glm::vec2(mScale.x * 0.4f, 50.0f));
=======
    quitGame->SetPosition(glm::vec2(mScale.x * 0.35f, mScale.y / 2 + 100.0f));
    quitGame->SetScale(glm::vec2(mScale.x * 0.4f, 20.0f));
>>>>>>> bf8cac53ce5ecb9bd4526344924f697b542a919c
    quitGame->SetForeColor(glm::vec3(1.0f));
    quitGame->SetHoverColor(glm::vec4(0.0f));
    quitGame->SetText("Quit Game");

 
    AddElement(resumeGame);
    AddElement(saveGame);
    AddElement(quitGame);

    
    
    return true;
}

void GUIPauseMenu::RenderBackground(Renderer *renderer, TextRenderer *text){
    renderer->Render(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(EventManager::GetScreenWidth(), EventManager::GetScreenHeight()), 0.0f);
    // render title
<<<<<<< HEAD
    text->RenderText("PAUSED", 320.0f, EventManager::GetScreenHeight() / 2 - 300.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
=======
    text->RenderText("PAUSED GAME", 360.0f, EventManager::GetScreenHeight() / 2 - 300.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
>>>>>>> bf8cac53ce5ecb9bd4526344924f697b542a919c
}

void GUIPauseMenu::Activate() {
    Game::GetInstance()->GetAudio()->StopAll();
<<<<<<< HEAD
    Game::GetInstance()->GetAudio()->PlaySound("Sounds/scratch.wav", true);
}

void GUIPauseMenu::Deactivate() {
    Game::GetInstance()->GetAudio()->PlaySound("Sounds/scratch.wav");
=======
    Game::GetInstance()->GetAudio()->PlaySound("Sounds/the_final_battle.wav", true);
}

void GUIPauseMenu::Deactivate() {
    Game::GetInstance()->GetAudio()->PlaySound("Sounds/the_final_battle.wav");
>>>>>>> bf8cac53ce5ecb9bd4526344924f697b542a919c
}

void GUIPauseMenu::ButtonPressed(std::shared_ptr<GUIButton> button){
    std::string buttonName = button->GetName();
    if(buttonName == "resumeGame"){
        Game::GetInstance()->SwitchStates(GAME_ACTIVE);
    } else if (buttonName == "quitGame"){
        Game::GetInstance()->SwitchStates(GAME_NULL);
    } else if (buttonName == "saveGame") {
        
    } else {
        // do nothing
    }
}

void GUIPauseMenu::Update(float dt){
    
};



